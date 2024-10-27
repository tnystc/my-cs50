import re

url = input("URL: ").strip()

#username = url.replace("https://twitter.com", "") BAD
#url.removeprefix() BAD

#username = re.sub(r"^(https?://)?(www\.)?twitter\.com/", "", url)

if matches := re.search(r"^(?:https?://)?(?:www\.)?twitter\.com/(\w+)$", url, re.IGNORECASE):
    print(f"Username: {matches.group(1)}")