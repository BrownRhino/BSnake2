import bottle
import os
import random
import PQ

@bottle.route('/static/<path:path>')
def static(path):
    return bottle.static_file(path, root='static/')


@bottle.post('/start')
def start():
    data = bottle.request.json
    game_id = data['game_id']
    board_width = data['width']
    board_height = data['height']

    head_url = '%s://%s/static/head.png' % (
        bottle.request.urlparts.scheme,
        bottle.request.urlparts.netloc
    )

    # TODO: Do things with data

    return {
        'color': '#00FF00',
        'taunt': '{} ({}x{})'.format(game_id, board_width, board_height),
        'head_url': head_url,
        'name': 'battlesnake-python'
    }


@bottle.post('/move')
def move():
	data = bottle.request.json
#	for key in data.keys():
#		print("KEY:  ",key)
#		print("DATA:   ",data[key])
    # TODO: Do things with data
	directions = ['up', 'down', 'left', 'right']

	#Where is the food located on the board
	food=data['food']

	#us: Contains information about our snake.  Assigned in the for loop below using the id of the snake
	id=data['you']
	
	#enemies: dictionary contains snake's id as the key which refers to a list containing the following: head position, body position and its size
	enemies=[]

	#obstacle: array will contain the locations of the board occupied by snakes (incl. yourself)
	obstacles=[]
    
	us={}
	for val in data['snakes']:
		for postn in val["coords"]:
			obstacles.append(tuple(postn))	
		if val['id']==id:
			us=val
			continue
		#Now that we know the snake isn't ours, it must be an enemy snake so we add them to the opposing snake structure
		opposing_snake={}
		opposing_snake['id']=val['id']
		opposing_snake['head']=val["coords"][0]
		opposing_snake['tail']=val["coords"][-1]
		opposing_snake["hp"]=val["health_points"]
		opposing_snake["coords"]=val["coords"]
		opposing_snake['size']=len(val['coords'])
		enemies.append(opposing_snake)

	start=us['coords'][0]
	print("Our Snake's Stats:")
	print(us)
	print()
	print("Obstacles:")
	print(obstacles)
	print()
	print("Tail Location:")
	print(us['coords'][-1])
	print()
	print("Enemy Snakes:")
	print(enemies)
	print()
	print("Food:")
	print(food[0])
	print()
	print("Head location")
	print(us['coords'][0])
	print("Path to Food Exists?")
	path=PQ.isReachable(us['coords'][0],food[0],obstacles)
	print(path)
	print()

	go = 'right'
	if path:
		path=PQ.aStar(us['coords'][0],food[0],obstacles)
		print("Path to Food:")
		print(path)
		print()
	
		finish=path[1]
		if(start[0]-finish[0])==0:
			if start[1]<finish[1]:
				go='down'
			else:
				go='up'
		else:
			if(start[0]<finish[0]):
				go='right'
			else:
				go='left'

	else:
#		obstacles.remove(tuple(us['coords'][-1])) #I THINK WE SHOULD REMOVE THE TAILS OF ALL SNAKES FROM OBSTACLES
		path=PQ.isReachable(us['coords'][0],us['coords'][-1],obstacles[:-1])
		print("Is there a path to our tail?")
		print(path)
		print()
		if path:
			path=PQ.aStar(us['coords'][0],us['coords'][-1],obstacles[:-1])
			print("Path to Tail:")
			print(path)
			print()

			finish=path[1]
			if(start[0]-finish[0])==0:
				if start[1]<finish[1]:
					go='down'
				else:
					go='up'
			else:
				if(start[0]<finish[0]):
					go='right'
				else:
					go='left'

			
	return {
		'move': go,
		'taunt': 'battlesnake-python!'
	}


# Expose WSGI app (so gunicorn can find it)
application = bottle.default_app()
if __name__ == '__main__':
    bottle.run(application, host=os.getenv('IP', '0.0.0.0'), port=os.getenv('PORT', '8080'))
