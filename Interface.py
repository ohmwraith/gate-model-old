
def get_content(way):
    with open(way, "r") as interface:
        return interface.read()

def get_lines(way):
    with open(way, "r") as interface:
        return interface.readlines()
def extract_data(data):
    array = []
    current_object_pointer = -1
    for line in data:
        if line == '' or line == '\n' or not (line.find(':') != -1 or line.find('=') != -1):
            continue
        if line[-2] == ':':
            array.append({"Object": line.replace(':\n', '')})
            current_object_pointer += 1
        else:
            line = line.replace('\n', '')
            array[current_object_pointer].setdefault(line.split("=")[0], line.split("=")[1])

    return array
def clean_interface(way):
    with open(way, "w") as interface:
        interface.truncate()
        interface.close()
    return True