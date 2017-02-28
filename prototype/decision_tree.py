import json
from enum import Enum
from random import randint
import math

# sample data
data = json.loads('{"turn": 1, "dead_snakes": [], '
               '"you": "ac29bf3f-999a-49eb-9aac-bb7bbc44859a", '
               '"game_id": "fe013c0f-6100-489e-a5f8-20c59548c927", '
               '"height": 20, '
               '"food": [[10, 11], [13, 14]], '
               '"width": 20, '
               '"snakes": [{"health_points": 99, '
                    '"id": "ac29bf3f-999a-49eb-9aac-bb7bbc44859a", '
                    '"taunt": "fe013c0f-6100-489e-a5f8-20c59548c927 (20x20)", '
                    '"name": "battlesnake-python", '
                    '"coords": [[15, 1], [15, 2], [15, 2]]}]}')

class Action (Enum):
    position = 1
    food = 2
    wander = 3

# getting our snake data
team_snake = None
for snake in data['snakes']:
    if snake['id'] == data['you']:
        team_snake = snake

# Setting random coordinates for now.
# Will get nearest food with the safest from dijkstra
nearest_food = [10, 8]

print(team_snake)
print(team_snake['health_points'])

# setting to 40 for now. It should be # of moves to nearest food + 20%
# hungry = # of moves to nearest food + 20% > teamSnake['health_points']
min_health = 40

my_x = team_snake['coords'][0][0]
my_y = team_snake['coords'][0][1]

# if hungry
if team_snake['health_points'] <= min_health:
    dist_to_apple = math.sqrt(((nearest_food[0] - my_x) ** 2) + ((nearest_food[1] - (my_y - 1)) ** 2))
    # if food within 20 sqrs
    if dist_to_apple < 12:
        # return Action.position
        print("returning Action.position")
    else:
        # return Action.food
        print("returning Action.food")
else:
    dist_to_apple = math.sqrt(((nearest_food[0] - my_x) ** 2) + ((nearest_food[1] - (my_y - 1)) ** 2))
    # if close to food. might as well get it. Arbitary value 10.
    if dist_to_apple < 10:
        # return Action.food
        print("returning Action.food")
    else:
        # setting in_area_domain to a random boolean value for now. Will get this from dijkstra
        # this checks if the closet food to us is in our area of domain. (voronoi)
        in_area_domain = randint(0, 9) > 5
        if in_area_domain:
            # return Action.wander
            print("returning Action.wander")
        else:
            # return Action.position
            print("returning Action.position")
