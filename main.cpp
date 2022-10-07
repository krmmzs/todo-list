#include <iostream>
#include <string>
#include <list>
#include <ctime>
#include <map>

class TodoItem {

private:
    int id = 0;
    std::string description = "";
    bool completed = false;

public:
    TodoItem() = default;
    TodoItem(TodoItem &&) = default;
    TodoItem(const TodoItem &) = default;
    TodoItem &operator=(TodoItem &&) = default;
    TodoItem &operator=(const TodoItem &) = default;
    ~TodoItem() = default;

    int getId() {
        return id;
    }

    std::string getDescription() {
        return description;
    }

    bool isCompleted() {
        return completed;
    }

    bool create(std::string new_description) {
        id = rand() % 100 + 1;
        description = new_description;
        return true;
    }

    void setCompleted(bool val) {
        completed = val;
    }


};

int state_code;
std::map<int, TodoItem> todoItems;

void set_status_code(int x) {
    state_code = x;
}

void check_status_code(int state_code) {
    if (state_code == 0) {
        return;
    } else if (state_code == 1) {
        std::cout <<  "No this TodoItem." << std::endl;
        std::cout <<  "Please re-enter!" << std::endl;
    }
}

int main (int argc, char *argv[])
{
    char input_option;
    int input_id;
    std::string input_description;
    std::string version = "v0.2.0";
    // std::list<TodoItem> todoItems;
    std::map<int, TodoItem>::iterator it;
    srand(time(nullptr));

    // todoItems.clear();

    // TodoItem test;
    // test.create("this is a test.");
    // todoItems.push_back(test);

    while (true) {
        system("clear");
        std::cout << "Todo List Maker - " << version << std::endl;
        std::cout << std::endl << std::endl;

        check_status_code(state_code);
        for (it = todoItems.begin(); it != todoItems.end(); it ++) {

            std:: string completed = it->second.isCompleted() ? "done" : "not done";

            std::cout << it->second.getId() << " | " << it->second.getDescription() << " | "
                << completed << std::endl;
        }

        if (todoItems.empty()) {
            std::cout << "Add your first todo!" << std::endl;
        }

        std::cout << "[a]dd a new Todo" << std::endl;
        std::cout << "[c]complete a Todo" << std::endl;
        std::cout << "[q]uit" << std::endl;

        std::cout << "choice: ";

        std::cin >> input_option;

        if (input_option == 'q') {
            std::cout << "Have a great day now!" << std::endl;
            break;
        } else if (input_option == 'c') {
            std::cout << "Enter id to mark completed." << std::endl;
            std::cin >> input_id;

            if (todoItems.find(input_id) == todoItems.end()) {
                set_status_code(1);
                continue;
            } else {
                set_status_code(0);
                todoItems[input_id].setCompleted(true);
            }

            todoItems[input_id].setCompleted(true);
        } else if (input_option == 'a') {
            set_status_code(0);
            std::cout << "Add a new description: ";
            std::cin.clear();
            std::cin.ignore();

            std::getline(std::cin, input_description);

            TodoItem newItem;
            newItem.create(input_description);
            todoItems[newItem.getId()] = newItem;
        }
    }

    return 0;
}
