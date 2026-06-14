import json
import os

FILE_NAME = "tasks.json"

def load_tasks():
    if not os.path.exists(FILE_NAME):
        return []
    with open(FILE_NAME, "r", encoding="utf-8") as file:
        return json.load(file)

def save_tasks(tasks):
    with open(FILE_NAME, "w", encoding="utf-8") as file:
        json.dump(tasks, file, ensure_ascii=False, indent=4)

def show_tasks(tasks):
    if not tasks:
        print("目前沒有任務")
        return

    for i, task in enumerate(tasks, start=1):
        status = "完成" if task["done"] else "未完成"
        print(f"{i}. {task['title']} [{status}]")

def add_task(tasks):
    title = input("請輸入任務名稱：")
    tasks.append({"title": title, "done": False})
    save_tasks(tasks)
    print("任務已新增")

def complete_task(tasks):
    show_tasks(tasks)
    num = int(input("請輸入要完成的任務編號："))
    if 1 <= num <= len(tasks):
        tasks[num - 1]["done"] = True
        save_tasks(tasks)
        print("任務已標記完成")

def delete_task(tasks):
    show_tasks(tasks)
    num = int(input("請輸入要刪除的任務編號："))
    if 1 <= num <= len(tasks):
        tasks.pop(num - 1)
        save_tasks(tasks)
        print("任務已刪除")

def main():
    tasks = load_tasks()

    while True:
        print("\n===== AI Todo List =====")
        print("1. 查看任務")
        print("2. 新增任務")
        print("3. 完成任務")
        print("4. 刪除任務")
        print("5. 離開")

        choice = input("請選擇功能：")

        if choice == "1":
            show_tasks(tasks)
        elif choice == "2":
            add_task(tasks)
        elif choice == "3":
            complete_task(tasks)
        elif choice == "4":
            delete_task(tasks)
        elif choice == "5":
            print("程式結束")
            break
        else:
            print("輸入錯誤，請重新選擇")

if __name__ == "__main__":
    main()