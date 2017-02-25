X_SIZE = 20
Y_SIZE = 20

import time
from heapq import heappush, heappop
from queue import *
import random
#import pdb
#pdb.set_trace()

def print_costs(costs):
    for y in range (Y_SIZE-1, -1, -1):
        for x in range (X_SIZE):
            if costs[(x,y)] < 2:
                print('   ',end='')
            elif costs[(x,y)] < 4:
                print('\u2591\u2591\u2591', end='')
            elif costs[(x,y)] < 6:
                print('\u2592\u2592\u2592', end='')
            elif costs[(x,y)] < 8:
                print('\u2593\u2593\u2593', end='')
            else:
                print('\u2588\u2588\u2588',end='')
        print('')

def print_steps(steps):
    for y in range (Y_SIZE-1, -1, -1):
        for x in range (X_SIZE):
                print(' ',end='')
                if steps[(x,y)] < 10:
                    print(' ', end='')
                print(steps[(x,y)], end='')
                print(' ', end='')
        print('')

def print_voronoi(steps, steps_list):
    for y in range (Y_SIZE-1, -1, -1):
        for x in range (X_SIZE):
            print(' ',end='')

            lowest_enemy_steps = min([d[(x,y)] for d in steps_list])
            
            if steps[(x,y)] < lowest_enemy_steps:
                print('\u2588',end='')
            elif steps[(x,y)] > lowest_enemy_steps:
                print('\u2591',end='')
            else:
                print('\u2593',end='')
            print(' ',end='')
        print('')

def is_inside_voronoi_boundry(x, y, steps, steps_list):
    return steps[x,y] < min([d[(x,y)] for d in steps_list])

impassible_limit = 10
def is_accessible( dijkstra_data, accessible, coords, steps_list):
    #print("------------Starting at point", coords)
    costs = dijkstra_data[2]
    stack = []
    stack.append(coords);
    while len(stack) > 0:
        #print("Stack has",len(stack),"things in it")
        if stack[-1] in accessible:
            if stack[-1] == coords:
                break;
            #print("Have data on", stack[-1],", is it accessible:",accessible[stack[-1]])
            #Point is accessible, previous is accessible, not inside someone else's boundry
            accessible[stack[-2]] = (not costs[stack[-2]] > impassible_limit) and (accessible[stack[-1]]) and (dijkstra_data[3][stack[-2]] < min([d[stack[-2]] for d in steps_list]))
            #print("Setting data for ", stack[-2], "to",accessible[stack[-2]])
            stack.pop()
        elif costs[stack[-1]] > impassible_limit:
              #print(stack[-1],"is inaccessible!")
              accessible[stack[-1]] = False
        else:
            #print("No data on", stack[-1])
            path_prev = dijkstra_data[0][stack[-1]]
            #print("Adding", path_prev)
            stack.append(path_prev)
    return accessible[coords]


def find_accessible_areas(start_point, dijkstra_data, steps_list, run_only=False):
    accessible = {}
    accessible[start_point] = dijkstra_data[3][start_point] < impassible_limit
    for y in range (Y_SIZE-1, -1, -1):
        for x in range (X_SIZE):
            if not run_only:
                print(' ',end='')
            if is_accessible(dijkstra_data, accessible, (x,y), steps_list):
                if not run_only:
                    print('\u2591', end='')
            else:
                if not run_only:
                    print('\u2588', end='')
            if not run_only:
                print(' ',end='')
        if not run_only:
            print('')
    return accessible

            

def print_paths(path, costs):
    for y in range (Y_SIZE-1, -1, -1):
        for x in range (X_SIZE):
            delta_x = path[x,y][0] - x
            delta_y = path[x,y][1] - y
            if costs[(x,y)] < 2:
                bg = ' '
            elif costs[(x,y)] < 4:
                bg = '\u2591'
            elif costs[(x,y)] < 6:
                bg = '\u2592'
            elif costs[(x,y)] < 8:
                bg = '\u2593'
            else:
                bg = '\u2588'
                
            if delta_y == -1:
                # V
                arrow = '\u25bc'
            elif delta_y == 1:
                # ^
                arrow = '\u25b2'
            elif delta_x == -1:
                # <
                arrow = '\u25c4'
            elif delta_x == 1:
                # >
                arrow = '\u25ba'
            else:
                arrow = '*'
            
            print(bg, end='')
            print(arrow, end='')
            print(bg, end='')
        print('')

def calc_accessible_area(coords, accessible):
    area = 0
    if not accessible[coords]:
        return 0
    mapped = {}
    queue = Queue()
    queue.put(coords)
    while queue.qsize() > 0:
        current_coord = queue.get()
        if current_coord not in mapped:
            mapped[current_coord] = True
            area = area + 1
            for next_coord in [(-1,0),(1,0),(0,-1),(0,1)]:
                x_new = current_coord[0]+next_coord[0]
                y_new = current_coord[1]+next_coord[1]
                if x_new >= 0 and x_new < X_SIZE and y_new >= 0 and y_new < Y_SIZE and accessible[(x_new,y_new)]:
                    queue.put((x_new,y_new))
    return area
            
            
            
            
                
def dijkstra (i, j, costs_input=None):
    graph_dict = {}
    costs={}
    prev={}
    dist={}
    steps={}

    queue = []
    
    for x in range (X_SIZE):
        for y in range (Y_SIZE):
            if costs_input is None:
                costs[(x,y)] = random.randint(1, 15)
            else:
                costs[(x,y)] = costs_input[(x,y)]
            dist[(x,y)] = 1000000
    
    heappush(queue, (0,(i,j),(i,j), 0))
    dist[(i,j)] = 0
    steps[(i,j)] = 0
    
    while len(queue) > 0:
        next_edge = heappop(queue)

        u = next_edge[1]
        v = next_edge[2]
        current_cost = next_edge[0]
        current_steps = next_edge[3];

        #if v == (i,j):
            #print(u, v, current_cost, dist[v])

        if not v in prev:
            prev[v] = u
            dist[v] = current_cost
            steps[v] = current_steps

            for next_node in [(-1,0),(1,0),(0,-1),(0,1)]:
                x_new = v[0]+next_node[0]
                y_new = v[1]+next_node[1]
                if x_new >= 0 and x_new < X_SIZE and y_new >= 0 and y_new < Y_SIZE:
                    new_cost = current_cost + costs[(x_new,y_new)]  
                    heappush(queue, (new_cost, v, (x_new,y_new), current_steps + 1))

        elif current_cost < dist[v]:
            prev[v] = u
            dist[v] = new_cost
            steps[v] = current_steps
    return (prev, dist, costs, steps)

t0 = time.process_time()
for timer in range(0,1000):
    path = dijkstra(random.randint(0,X_SIZE-1),random.randint(0,Y_SIZE-1))
    if timer % 100 == 0:
        print (timer, '/', 1000)
path = dijkstra(0,0)
t1 = time.process_time()

#print(path[0])
#print(path[1])
print((t1-t0), 'milliseconds to run at', X_SIZE, 'by', Y_SIZE)

test_graph = {}
for x in range (X_SIZE):
    for y in range (Y_SIZE):
        test_graph[(x,y)] = 1
for x in range(1, X_SIZE//2):
    for y in range (1, Y_SIZE-1):
        test_graph[(x*2,y)] = 100
        if x%2 == 0:
            test_graph[(x*2,0)] = 100
        else:
            test_graph[(x*2,Y_SIZE-1)] = 100

test_results = dijkstra(X_SIZE//2, Y_SIZE//2,test_graph)
print_paths(test_results[0], test_results[2])

print()
print()

test_graph = {}
for x in range (X_SIZE):
    for y in range (Y_SIZE):
        test_graph[(x,y)] = 1
for x in range(1, X_SIZE//2):
    for y in range (1, Y_SIZE-1):
        test_graph[(x*2,y)] = random.randint(1,10)
        if x%2 == 0:
            test_graph[(x*2,0)] = random.randint(1,10)
        else:
            test_graph[(x*2,Y_SIZE-1)] = random.randint(1,10)

test_results = dijkstra(X_SIZE//2 - 1, Y_SIZE//2,test_graph)
print_paths(test_results[0], test_results[2])
print_steps(test_results[3])

enemy_results = []
enemy_results.append(dijkstra(0,0,test_graph)[3])
enemy_results.append(dijkstra(X_SIZE-1,Y_SIZE-1,test_graph)[3])
enemy_results.append(dijkstra(0,Y_SIZE-1,test_graph)[3])
print_voronoi(test_results[3], enemy_results)
print()
print()
print("Accessible areas:")
accessible_areas = find_accessible_areas((X_SIZE//2-1, Y_SIZE//2), test_results, enemy_results)
print("Area=", calc_accessible_area((X_SIZE//2-1, Y_SIZE//2), accessible_areas))

t0 = time.process_time()
for timer in range(0,1000):
    myX = random.randint(0,X_SIZE-1)
    myY = random.randint(0,Y_SIZE-1)
    path = dijkstra(myX, myY)
    enemy_results = []
    for enemy in range(0,9):
        enemy_results.append(dijkstra(random.randint(0,X_SIZE-1),random.randint(0,Y_SIZE-1),path[2])[3])
    find_accessible_areas((myX, myY), path, enemy_results, True)
    if timer % 100 == 0:
        print (timer, '/', 1000)
path = dijkstra(0,0)
t1 = time.process_time()

#print(path[0])
#print(path[1])
print((t1-t0), 'milliseconds to run at', X_SIZE, 'by', Y_SIZE, 'with 8 other snakes')
