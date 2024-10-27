import os
import re

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    user_id = session["user_id"]
    stocks = db.execute("SELECT symbol, SUM(shares) AS shares FROM transactions WHERE user_id = ? GROUP BY symbol", user_id)
    cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]
    stock_total = 0

    for item in stocks:
        shares = item["shares"]

        api_response = lookup(item["symbol"])
        price = api_response["price"]

        item["price"] = api_response["price"]
        item["name"] = api_response["name"]
        item["item_total"] = shares * price
        stock_total += item["item_total"]

    return render_template("index.html", stocks=stocks, cash=cash, total=stock_total+cash, usd=usd)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol").upper()
        try:
            shares = int(request.form.get("shares"))
        except:
            return apology("input is not a integer")
        api_response = lookup(symbol)

        if not api_response:
            return apology("invalid symbol", 400)

        if shares < 0:
            return apology("input is not a positive integer", 400)

        price = api_response["price"]
        user_id = session["user_id"]
        current_cash_db = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
        current_cash = current_cash_db[0]["cash"]
        new_cash = current_cash - price * shares

        if new_cash < 0:
            return apology("you cannot afford this transaction", 400)

        db.execute("UPDATE users SET cash = ? WHERE id = ?", new_cash, user_id)
        db.execute("INSERT INTO transactions (user_id, symbol, shares, price) VALUES (?, ?, ?, ?)", user_id, symbol, shares, price)

        flash("Bought!")
        return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    user_id = session["user_id"]

    transactions = db.execute("SELECT symbol, shares, price, date FROM transactions WHERE user_id = ?", user_id)

    return render_template("history.html", transactions=transactions, usd=usd)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        symbol = request.form.get("symbol").upper()
        api_response = lookup(symbol)

        if not api_response:
            return apology("invalid symbol", 400)

        name = api_response["name"]
        price = usd(api_response["price"])

        return render_template("quoted.html", name=name, symbol=symbol, price=price)

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        if not username:
            return apology("must provide username", 400)
        if not password:
            return apology("missing password", 400)
        if password != confirmation:
            return apology("passwords don't match", 400)

        special_symbols = ['!', '@', '#', '$', '%', '^', '&', '*']
        validation = True

        if len(password) <= 8:
            validaton = False

        if not any(char.isdigit() for char in password):
            validation = False

        if not any(char.isupper() for char in password):
            validation = False

        if not any(char.islower() for char in password):
            validation = False

        if not any(char in special_symbols for char in password):
            validation = False

        if not validation:
            return apology("password does not meet requirements", 400)

        try:
            id = db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, generate_password_hash(password))
        except:
            return apology("username already exists", 400)

        session["user_id"] = id
        flash("Registered!")
        return redirect("/")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    user_id = session["user_id"]

    if request.method == "POST":
        symbol = request.form.get("symbol")
        try:
            shares = int(request.form.get("shares"))
        except:
            return apology("missing shares")
        print(symbol)

        current_shares = db.execute(
            "SELECT SUM(shares) AS shares FROM transactions WHERE user_id = ? AND symbol = ?", user_id, symbol)[0]["shares"]

        if not symbol:
            return apology("missing symbol", 400)

        if shares < 1:
            return apology("input is not a positive integer", 400)

        if shares > current_shares:
            return apology("there is not enough shares", 400)

        cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]
        api_response = lookup(symbol)
        price = api_response["price"]
        total = cash + price * shares
        db.execute("UPDATE users SET cash = ? WHERE id = ?", total, user_id)

        db.execute("INSERT INTO transactions (user_id, symbol, shares, price) VALUES (?, ?, ?, ?)", user_id, symbol, -1*shares, price)

        flash("Sold!")
        return redirect("/")

    else:
        stocks = db.execute("SELECT symbol FROM transactions WHERE user_id = ? GROUP BY symbol", user_id)
        return render_template("sell.html", stocks=stocks)

