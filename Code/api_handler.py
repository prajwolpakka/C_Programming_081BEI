from learning_toolbox import generate_content, save_files
import sys
import io
sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8')

api_key = 'AIzaSyBZLoc-QlufDNo9fRhylpeKU3vBwB5xsQ4'


def main():
    if len(sys.argv) < 3:
        print("Error: Please provide topic and content type")
        return
    
    topic = sys.argv[1]
    content_type = sys.argv[2]
    
    content = generate_content(topic, content_type, api_key=api_key)
    
    if content:
        md_file, pdf_file = save_files(topic, content, content_type,base_dir="")
        
    
    print(content)

if __name__ == "__main__":
    main()
