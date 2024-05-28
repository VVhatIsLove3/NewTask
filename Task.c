import aiohttp
import asyncio
import aiofiles
from bs4 import BeautifulSoup
import re

links = [
    "https://regex101.com/",
        "https://docs.python.org/3/this-url-will-404.html",
        "https://www.nytimes.com/guides/",
        "https://www.mediamatters.org/",
        "https://1.1.1.1/",
        "https://www.politico.com/tipsheets/morning-money",
        "https://www.bloomberg.com/markets/economics",
        "https://www.ietf.org/rfc/rfc2616.txt"
]

async def fetch_html(session, url) :
    async with session.get(url) as response :
return await response.text()

async def parse_links(html) :
    soup = BeautifulSoup(html, 'html.parser')
    found_links = [link.get('href') for link in soup.find_all('a', href = True)]
    return found_links

    async def write_links_to_file(links) :
    async with aiofiles.open('found_links.txt', 'a') as file :
for link in links :
await file.write(link + '\n')

async def main() :
    async with aiohttp.ClientSession() as session :
tasks = [fetch_html(session, url) for url in links]
htmls = await asyncio.gather(*tasks)

all_found_links = []
for html in htmls :
found_links = await parse_links(html)
all_found_links.extend(found_links)

await write_links_to_file(all_found_links)

if name == '__main__':
asyncio.run(main())