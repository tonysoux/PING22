"""open the .uml and use plantuml.preview command or shortcut to see the diagram"""

import os
import time
from watchdog.observers import Observer
from watchdog.events import FileSystemEventHandler
import hpp2plantuml

folder2watch = "esp32"
puml_file_path = os.path.join(os.path.dirname(os.path.abspath(__file__)), folder2watch+".puml")
class MyHandler(FileSystemEventHandler):
    def on_modified(self, event):
        if event.src_path.endswith(".hpp"):
            generate_diagram()

def generate_diagram():
    hppFiles = [os.path.join(root, name) for root, dirs, files in os.walk(folder2watch) for name in files if name.endswith(".hpp")]
    hpp2plantuml.CreatePlantUMLFile(hppFiles, puml_file_path)
if __name__ == "__main__":
    
    generate_diagram()  # Generate diagram initially
    event_handler = MyHandler()
    observer = Observer()
    observer.schedule(event_handler, path=folder2watch, recursive=True)
    observer.start()

    try:
        while True:
            time.sleep(1)
    except KeyboardInterrupt:
        observer.stop()
    observer.join()