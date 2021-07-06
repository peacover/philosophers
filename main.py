import json
from sys import argv
lanch_path = r"/Users/yer-raki/Desktop/philosophers/.vscode/launch.json"
with open(lanch_path, "r") as file:
    data = json.load(file)

data['configurations'][0]['args'] = argv[1::]

with open(lanch_path, "w") as file:
    json.dump(data, file)