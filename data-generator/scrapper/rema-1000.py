import codecs
import math
import time
import json
from dataclasses import dataclass

from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.chrome.service import Service as ChromeService
from webdriver_manager.chrome import ChromeDriverManager

# !!! Warning this code is shit and slow, you have been warned traveller !!!
# PS. Fuck Python syntax

queries = {
    "https://shop.rema1000.dk/brod-kager/baguetteflutes",
    "https://shop.rema1000.dk/brod-kager/boller",
    "https://shop.rema1000.dk/brod-kager/brod",
    "https://shop.rema1000.dk/brod-kager/rugbrod",
    "https://shop.rema1000.dk/brod-kager/fast-food-brod",
    "https://shop.rema1000.dk/brod-kager/kager",
    "https://shop.rema1000.dk/brod-kager/bavinchi-bager",
    "https://shop.rema1000.dk/frugt-gront/paere-aeble-banan-citrusfrugt",
    "https://shop.rema1000.dk/frugt-gront/blommer-fersken-nektariner-kiwi",
    "https://shop.rema1000.dk/frugt-gront/melon-baer-vindruer-eksotisk-frugt",
    "https://shop.rema1000.dk/frugt-gront/agurk-tomat-peberfrugt",
    "https://shop.rema1000.dk/frugt-gront/salater-fint-gront-avocado",
    "https://shop.rema1000.dk/frugt-gront/friske-faerdige-salater",
    "https://shop.rema1000.dk/frugt-gront/krydderurter-smagsforstaerkere",
    "https://shop.rema1000.dk/frugt-gront/grov-gront",
    "https://shop.rema1000.dk/frugt-gront/kal",
    "https://shop.rema1000.dk/frugt-gront/kartofler-log",
    "https://shop.rema1000.dk/kod-fisk-fjerkrae/fisk-skaldyr",
    "https://shop.rema1000.dk/kod-fisk-fjerkrae/hakket-kod",
    "https://shop.rema1000.dk/kod-fisk-fjerkrae/kylling",
    "https://shop.rema1000.dk/kod-fisk-fjerkrae/oksekod",
    "https://shop.rema1000.dk/kod-fisk-fjerkrae/gris",
    "https://shop.rema1000.dk/kod-fisk-fjerkrae/lam",
    "https://shop.rema1000.dk/kod-fisk-fjerkrae/plantebaserede-alternativer",
    "https://shop.rema1000.dk/kod-fisk-fjerkrae/vildt",
    "https://shop.rema1000.dk/kod-fisk-fjerkrae/and",
    "https://shop.rema1000.dk/kol/bacon-og-toppings",
    "https://shop.rema1000.dk/kol/delikatesser",
    "https://shop.rema1000.dk/kol/plantebaserede-produkter",
    "https://shop.rema1000.dk/kol/dej",
    "https://shop.rema1000.dk/kol/dressing-og-saucer",
    "https://shop.rema1000.dk/kol/fisk-sild-og-skaldyr",
    "https://shop.rema1000.dk/kol/frisk-pasta",
    "https://shop.rema1000.dk/kol/faerdigretter",
    "https://shop.rema1000.dk/kol/palaeg",
    "https://shop.rema1000.dk/kol/postejpate",
    "https://shop.rema1000.dk/kol/polser",
    "https://shop.rema1000.dk/kol/palaegs-salater",
    "https://shop.rema1000.dk/frost/brod-og-kager",
    "https://shop.rema1000.dk/frost/fisk-og-skaldyr",
    "https://shop.rema1000.dk/frost/faerdigretter",
    "https://shop.rema1000.dk/frost/grontsagerfrugt-og-baer",
    "https://shop.rema1000.dk/frost/is-og-dessert",
    "https://shop.rema1000.dk/frost/pizza",
    "https://shop.rema1000.dk/frost/kartofler",
    "https://shop.rema1000.dk/frost/kod-og-fjerkrae",
    "https://shop.rema1000.dk/frost/suppe-og-suppefyld",
    "https://shop.rema1000.dk/mejeri/flode-mv",
    "https://shop.rema1000.dk/mejeri/gaer",
    "https://shop.rema1000.dk/mejeri/juice-kakao-drikkeyoghurt-mv",
    "https://shop.rema1000.dk/mejeri/koldskal",
    "https://shop.rema1000.dk/mejeri/maelk-mv",
    "https://shop.rema1000.dk/mejeri/maelkesnittedessert",
    "https://shop.rema1000.dk/mejeri/smor-og-fedtstoffer",
    "https://shop.rema1000.dk/mejeri/syrnede-produkter",
    "https://shop.rema1000.dk/mejeri/yoghurt-mv",
    "https://shop.rema1000.dk/mejeri/aeg",
    "https://shop.rema1000.dk/ost-mv/hytteost",
    "https://shop.rema1000.dk/ost-mv/plantebaseret",
    "https://shop.rema1000.dk/ost-mv/borneost",
    "https://shop.rema1000.dk/ost-mv/hard-ost",
    "https://shop.rema1000.dk/ost-mv/madlavningsost-mv",
    "https://shop.rema1000.dk/ost-mv/skiveskaret",
    "https://shop.rema1000.dk/ost-mv/skaereost",
    "https://shop.rema1000.dk/ost-mv/smoreost",
    "https://shop.rema1000.dk/ost-mv/specialost",
    "https://shop.rema1000.dk/kolonial/chips-og-snacks",
    "https://shop.rema1000.dk/kolonial/dressing",
    "https://shop.rema1000.dk/kolonial/fiskekonserves",
    "https://shop.rema1000.dk/kolonial/ketchup-remoulade-mayonnaise-mv",
    "https://shop.rema1000.dk/kolonial/kiks-kager-og-knaekbrod",
    "https://shop.rema1000.dk/kolonial/konserves-og-survarer",
    "https://shop.rema1000.dk/kolonial/krydderier",
    "https://shop.rema1000.dk/kolonial/margarine",
    "https://shop.rema1000.dk/kolonial/marmelade-og-chokolade-palaeg-mv",
    "https://shop.rema1000.dk/kolonial/mel-sukker-bagning",
    "https://shop.rema1000.dk/kolonial/morgenmad",
    "https://shop.rema1000.dk/kolonial/nodder-og-torret-frugt",
    "https://shop.rema1000.dk/kolonial/olie-eddike-og-balsamico",
    "https://shop.rema1000.dk/kolonial/ris-og-pasta-mv",
    "https://shop.rema1000.dk/kolonial/saucer-og-nem-mad",
    "https://shop.rema1000.dk/kolonial/tex-mex",
    "https://shop.rema1000.dk/drikkevarer/alkoholfri-olvin",
    "https://shop.rema1000.dk/drikkevarer/hedvinaperitif",
    "https://shop.rema1000.dk/drikkevarer/hvidvin",
    "https://shop.rema1000.dk/drikkevarer/mousserende-vin",
    "https://shop.rema1000.dk/drikkevarer/rosevin",
    "https://shop.rema1000.dk/drikkevarer/rodvin",
    "https://shop.rema1000.dk/drikkevarer/sodavand-vand-smoothies-mv",
    "https://shop.rema1000.dk/drikkevarer/ready-to-drink",
    "https://shop.rema1000.dk/drikkevarer/special-ol",
    "https://shop.rema1000.dk/drikkevarer/ol",
    "https://shop.rema1000.dk/drikkevarer/juice-mv",
    "https://shop.rema1000.dk/drikkevarer/saft-mv",
    "https://shop.rema1000.dk/drikkevarer/instant-kaffe",
    "https://shop.rema1000.dk/drikkevarer/kaffe",
    "https://shop.rema1000.dk/drikkevarer/kaffetilbehor",
    "https://shop.rema1000.dk/drikkevarer/kakao",
    "https://shop.rema1000.dk/drikkevarer/plantedrikke",
    "https://shop.rema1000.dk/drikkevarer/te",
    "https://shop.rema1000.dk/drikkevarer/energidrikke",
    "https://shop.rema1000.dk/husholdning/kemisk-teknisk",
    "https://shop.rema1000.dk/husholdning/dyreartikler",
    "https://shop.rema1000.dk/husholdning/hundemad",
    "https://shop.rema1000.dk/husholdning/kattemad",
    "https://shop.rema1000.dk/husholdning/fuglefoder",
    "https://shop.rema1000.dk/husholdning/fuglefoder",
    "https://shop.rema1000.dk/husholdning/el",
    "https://shop.rema1000.dk/husholdning/fodselsdag",
    "https://shop.rema1000.dk/husholdning/indpakningkort",
    "https://shop.rema1000.dk/husholdning/kontor-og-legetoj",
    "https://shop.rema1000.dk/husholdning/kokkenredskaber",
    "https://shop.rema1000.dk/husholdning/lys-og-servietter",
    "https://shop.rema1000.dk/husholdning/optaending",
    "https://shop.rema1000.dk/husholdning/papir-og-poser",
    "https://shop.rema1000.dk/husholdning/rengoringsartikler",
    "https://shop.rema1000.dk/husholdning/rengoringsmidler",
    "https://shop.rema1000.dk/husholdning/service",
    "https://shop.rema1000.dk/husholdning/textil",
    "https://shop.rema1000.dk/husholdning/toiletpapirkokkenruller",
    "https://shop.rema1000.dk/husholdning/vask-og-opvask",
    "https://shop.rema1000.dk/baby-og-smaborn/bleer",
    "https://shop.rema1000.dk/baby-og-smaborn/baby-og-smabornsmad",
    "https://shop.rema1000.dk/baby-og-smaborn/baby-bad",
    "https://shop.rema1000.dk/baby-og-smaborn/sutter",
    "https://shop.rema1000.dk/baby-og-smaborn/ammeindlaeg",
    "https://shop.rema1000.dk/baby-og-smaborn/diverse-baby",
    "https://shop.rema1000.dk/pers-pleje/ansigt",
    "https://shop.rema1000.dk/pers-pleje/barberartikler",
    "https://shop.rema1000.dk/pers-pleje/cremer-til-krophaender",
    "https://shop.rema1000.dk/pers-pleje/deodorant",
    "https://shop.rema1000.dk/pers-pleje/diverse",
    "https://shop.rema1000.dk/pers-pleje/har-styling",
    "https://shop.rema1000.dk/pers-pleje/kosttilskud",
    "https://shop.rema1000.dk/pers-pleje/lommelettervadservietterplaster",
    "https://shop.rema1000.dk/pers-pleje/laebepomade",
    "https://shop.rema1000.dk/pers-pleje/mundpleje",
    "https://shop.rema1000.dk/pers-pleje/shampoobalsam",
    "https://shop.rema1000.dk/pers-pleje/saebe",
    "https://shop.rema1000.dk/pers-pleje/vat-bind-og-tamponer",
    "https://shop.rema1000.dk/slik/bolcher",
    "https://shop.rema1000.dk/slik/chokolade-mv",
    "https://shop.rema1000.dk/slik/karamel-mv",
    "https://shop.rema1000.dk/slik/lakrids-mv",
    "https://shop.rema1000.dk/slik/mixposer",
    "https://shop.rema1000.dk/slik/pastiller",
    "https://shop.rema1000.dk/slik/skum",
    "https://shop.rema1000.dk/slik/tyggegummi",
    "https://shop.rema1000.dk/slik/vingummi",
    "https://shop.rema1000.dk/slik/marcipan-mv",
    "https://shop.rema1000.dk/slik/saeson",
    "https://shop.rema1000.dk/kiosk/spiritus",
    "https://shop.rema1000.dk/kiosk/shots",
    "https://shop.rema1000.dk/kiosk/tilbehor"
}


options = webdriver.ChromeOptions()
options.add_argument('--headless')
options.add_argument('--no-sandbox')
user_agent = "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/107.0.0.0 " \
             "Safari/537.36 "
options.add_argument(f'user-agent={user_agent}')
chrome_prefs = {}
options.experimental_options["prefs"] = chrome_prefs
chrome_prefs['chrome.page.customHeaders.referrer'] = "https://shop.rema1000.dk/"

driver = webdriver.Chrome(service=ChromeService(ChromeDriverManager().install()), options=options)


@dataclass
class Item:
    name = ""  # Name
    price = 0.0  # Price
    price_pr_unit = 0.0  # Price per unit
    pr_unit = ""  # Unit type for per unit
    unit_size = 0.0  # Size of unit
    unit_type = ""  # Type

    @classmethod
    def dict(cls):
        return {"name": cls.name,
                "price": cls.price,
                "price_pr_unit": {
                    "price": cls.price_pr_unit,
                    "unit": cls.pr_unit
                },
                "unit_size": cls.unit_size,
                "unit_type": cls.unit_type
                }

    @classmethod
    def json(cls):
        return json.dumps(cls.dict(), ensure_ascii=False, indent=2)


def make_request(_url):
    driver.get(_url)
    print("Scanning: ", driver.current_url)
    # print("Page Title:", driver.title)
    time.sleep(5)
    retVal = driver.find_elements(By.CLASS_NAME, "info")
    return retVal


def html_to_items(_content, _items):
    for element in _content:
        item = Item
        divs = element.find_elements(By.TAG_NAME, "div")
        for div in divs:
            _class = div.get_attribute("class")
            if _class == "title":
                item.name = div.get_attribute("innerText")
            elif _class == "price":
                textlist = div.get_attribute("innerText").split(" ")
                price = textlist[0]
                price_len = len(price) - 2
                item.price = float((price[:price_len] + "." + price[price_len:]).replace(",", ""))
                item.price_pr_unit = float(textlist[1].replace(",", ""))
                item.pr_unit = textlist[3].replace(".", "")
            elif _class == "extra":
                textlist = div.get_attribute("innerText").split(" ")
                item.unit_size = float(textlist[0].replace(",", ""))
                item.unit_type = textlist[1].replace(".", "")

        if item.name != "":
            _items.append(item.json())

    return _items


def items_to_json(_items):
    retVal = "[\n"
    for i in range(0, len(_items)):
        if i != 0:
            retVal += ",\n"
        retVal += _items[i]
    retVal += "\n]"
    return retVal


if __name__ == '__main__':
    items = []
    _len = len(queries)
    _index = 1
    for url in queries:
        content = make_request(url)
        items = html_to_items(content, items)
        print("Progress: " + str(math.ceil(_index/_len * 100)) + "%")
        _index += 1

    json_string = items_to_json(items)
    with codecs.open('rema-1000.json', 'w', encoding='utf-8') as file:
        file.write(json_string)
