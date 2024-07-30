

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>


// Структура для представления узла бинарного дерева поиска
struct Node {
    std::string key; // Английское слово
    std::string value; // Русское слово
    Node* left;
    Node* right;

    // Конструктор для инициализации узла
    Node(std::string k, std::string v) : key(k), value(v), left(nullptr), right(nullptr) {}
};


// Класс для бинарного дерева поиска
class BinarySearchTree {
private:

    // Вставка узла в дерево
    Node* insertNode(Node* root, std::string key, std::string value) {
        // Если дерева нет, создаем новый узел
        if (!root) {
            return new Node(key, value);
        }

        // Рекурсивный поиск позиции для вставки нового узла
        if (key < root->key) {
            root->left = insertNode(root->left, key, value);
        }
        else if (key > root->key) {
            root->right = insertNode(root->right, key, value);
        }

        return root;
    }

    // Поиск узла в дереве
    Node* searchNode(Node* root, std::string key) {
        // Если корень пуст или ключ найден, возвращаем узел
        if (!root || root->key == key) {
            return root;
        }

        // Рекурсивный поиск
        if (key < root->key) {
            return searchNode(root->left, key);
        }
        else {
            return searchNode(root->right, key);
        }
    }

public:
    Node* root; // Корень дерева

    // Конструктор для инициализации дерева
    BinarySearchTree() : root(nullptr) {}

    // Функция для вставки новой пары ключ-значение
    void insert(std::string key, std::string value) {
        root = insertNode(root, key, value);
    }

    // Функция для поиска значения по ключу
    std::string search(std::string key) {
        Node* result = searchNode(root, key); // Поиск узла
        if (result) {
            return result->value; // Возвращаем перевод
        }
        else {
            return "Перевод не найден";
        }
    }

    /// <summary>
    /// Загрузка словаря из файла
    /// </summary>
    /// <param name="filename"> Название файла  </param>
    void loadDictionaryFromFile(const std::string& filename) {
        std::ifstream file;
        file.open(filename, std::ios::in);
        if (!file.is_open()) {
            std::cerr << "Error opening file: " << filename << std::endl;
            return;
        }

        std::string line;
        // Чтение файла построчно
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string key, value;
            // Разделение строки на ключ и значение по символу ':'
            if (std::getline(iss, key, ':') && std::getline(iss, value)) {
                insert(key, value);
            }
        }

        file.close();
    }

    // Функция для печати дерева
    void printTree(Node* root, int level = 0) {
        if (root) {
            printTree(root->right, level + 1);
            std::cout << root->key << " : " << root->value << std::endl;
            printTree(root->left, level + 1);
        }
    }
};

int main() {
    setlocale(LC_ALL, "rus");
    BinarySearchTree dictionary; // Создание экземпляра дерева

    // Загружаем слова из файла "dictionary.txt"
    dictionary.loadDictionaryFromFile("dictionary.txt");

    std::cout << "Содержимое дерева:" << std::endl;
    dictionary.printTree(dictionary.root);

    // Проверим поиск по словам
    std::cout << "Перевод слова 'apple': " << dictionary.search("apple") << std::endl;
    std::cout << "Перевод слова 'mouse': " << dictionary.search("mouse") << std::endl;
    std::cout << "Перевод слова 'cat': " << dictionary.search("cat") << std::endl;
    std::cout << "Перевод слова 'aDle': " << dictionary.search("aDle") << std::endl;

    return 0;
}