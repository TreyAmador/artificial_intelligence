# script to analyze data
import pprint


path = 'tests/clean_data.txt'
heur = ['Manhattan Heuristic','Misplaced Heuristic']


def heuristic():
    return {
        heur[0]:{'time':0,'visit':0,'count':0},
        heur[1]:{'time':0,'visit':0,'count':0}}


def init_data():
    keys = [ x for x in range(2,21,2) ]
    data = { key:heuristic() for key in keys }
    return keys,data


def process(line):
    elem = [x.strip() for x in line.split(',')]
    elem[0] = int(elem[0])
    elem[2] = int(elem[2])
    elem[3] = float(elem[3])
    return elem
    

def summation(data,elem):
    depth = elem[0]
    heur = elem[1]
    data[depth][heur]['visit'] += elem[2]
    data[depth][heur]['time'] += elem[3]
    data[depth][heur]['count'] += 1


def mean(data,elem):
    depth = elem[0]
    heur = elem[1]
    count = data[depth][heur]['count']
    data[depth][heur]['visit']  /= count
    data[depth][heur]['time'] /= count
    data[depth][heur]['count'] /= count


def read_file(keys,data):
    with open('tests/output.txt') as f_obj:
        for line in f_obj:
            elem = process(line)
            summation(data,elem)
            mean(data,elem)


def write_file(keys,data,path):
    with open(path,'wt') as f_obj:
        for k in keys:
            f_obj.write('Depth: '+str(k)+' ')
            for h in heur:
                f_obj.write('Heuristic: '+str(h)+' ')
                f_obj.write('Nodes: '+str(data[k][h]['visit'])+' ')
                f_obj.write('Time: '+str(data[k][h]['time'])+'\n')


def printer(data):
    pp = pprint.PrettyPrinter()
    pp.pprint(data)


def run():
    keys,data = init_data()
    read_file(keys,data)
    printer(data)
    write_file(keys,data,path)


run()

