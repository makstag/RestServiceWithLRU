import requests


def post(key, value):
    print(requests.post('http://localhost:8080/key',
          json={"key": key, "value": value}).content)


def get(key):
    print(requests.get('http://localhost:8080/key', json={"key": key}).content)


# x = requests.post('http://localhost:8080/key', json={"key": 2, "value": 3})
# x = requests.get('http://localhost:8080/key', json={"key": 2})
# print(x._content)

post(1, 1)
post(2, 2)
get(1)
post(3, 3)
get(2)
post(4, 4)
get(1)
get(3)
get(4)
