#include <iostream>
#include <cmath>
using namespace std;

#define MAX_NAME_SIZE 100
#define MAX_RESERVOIRS 50

class Reservoir {
private:
    char name[MAX_NAME_SIZE];
    char type[MAX_NAME_SIZE];
    double width;
    double length;
    double maxDepth;

    int stringLength(const char* str) const {
        int len = 0;
        while (str[len] != '\0') len++;
        return len;
    }

    void copyString(char* dest, const char* src) const {
        int i = 0;
        while (src[i] != '\0') {
            dest[i] = src[i];
            i++;
        }
        dest[i] = '\0';
    }

    int compareStrings(const char* str1, const char* str2) const {
        int i = 0;
        while (str1[i] != '\0' && str2[i] != '\0') {
            if (str1[i] != str2[i]) {
                return (str1[i] > str2[i]) ? 1 : -1;
            }
            i++;
        }
        if (str1[i] == '\0' && str2[i] == '\0') return 0;
        return (str1[i] == '\0') ? -1 : 1;
    }

public:
    Reservoir() {
        name[0] = '\0';
        type[0] = '\0';
        width = 0.0;
        length = 0.0;
        maxDepth = 0.0;
    }

    explicit Reservoir(const char* n, const char* t = "Озеро", double w = 1.0, double l = 1.0, double d = 1.0) {
        copyString(name, n);
        copyString(type, t);
        width = w;
        length = l;
        maxDepth = d;
    }

    Reservoir(const Reservoir& other) {
        copyString(name, other.name);
        copyString(type, other.type);
        width = other.width;
        length = other.length;
        maxDepth = other.maxDepth;
    }

    Reservoir& operator=(const Reservoir& other) {
        if (this != &other) {
            copyString(name, other.name);
            copyString(type, other.type);
            width = other.width;
            length = other.length;
            maxDepth = other.maxDepth;
        }
        return *this;
    }

    const char* getName() const { return name; }
    const char* getType() const { return type; }
    double getWidth() const { return width; }
    double getLength() const { return length; }
    double getMaxDepth() const { return maxDepth; }

    void setName(const char* n) { copyString(name, n); }
    void setType(const char* t) { copyString(type, t); }
    void setWidth(double w) { width = w; }
    void setLength(double l) { length = l; }
    void setMaxDepth(double d) { maxDepth = d; }

    double calculateVolume() const {
        return width * length * maxDepth;
    }

    double calculateSurfaceArea() const {
        return width * length;
    }

    bool isSameType(const Reservoir& other) const {
        return compareStrings(type, other.type) == 0;
    }

    bool compareSurfaceArea(const Reservoir& other) const {
        if (!isSameType(other)) {
            return false;
        }
        return calculateSurfaceArea() > other.calculateSurfaceArea();
    }

    void copyFrom(const Reservoir& other) {
        *this = other;
    }

    void displayInfo() const {
        cout << "Назва: " << name << endl;
        cout << "Тип: " << type << endl;
        cout << "Ширина: " << width << " м" << endl;
        cout << "Довжина: " << length << " м" << endl;
        cout << "Максимальна глибина: " << maxDepth << " м" << endl;
        cout << "Об'єм: " << calculateVolume() << " м³" << endl;
        cout << "Площа поверхні: " << calculateSurfaceArea() << " м²" << endl;
    }
};

class ReservoirArray {
private:
    Reservoir reservoirs[MAX_RESERVOIRS];
    int count;

public:
    ReservoirArray() : count(0) {}

    bool addReservoir(const Reservoir& reservoir) {
        if (count < MAX_RESERVOIRS) {
            reservoirs[count] = reservoir;
            count++;
            cout << "Водойма додана успішно!" << endl;
            return true;
        }
        cout << "Масив переповнений!" << endl;
        return false;
    }

    bool removeReservoir(int index) {
        if (index < 0 || index >= count) {
            cout << "Неправильний індекс!" << endl;
            return false;
        }
        for (int i = index; i < count - 1; i++) {
            reservoirs[i] = reservoirs[i + 1];
        }
        count--;
        cout << "Водойма видалена успішно!" << endl;
        return true;
    }

    void displayAll() const {
        if (count == 0) {
            cout << "Масив порожній" << endl;
            return;
        }
        cout << "Всього водойм: " << count << endl;
        for (int i = 0; i < count; i++) {
            cout << "\n--- Водойма " << i + 1 << " ---" << endl;
            reservoirs[i].displayInfo();
        }
    }

    Reservoir* getReservoir(int index) {
        if (index >= 0 && index < count) {
            return &reservoirs[index];
        }
        return nullptr;
    }

    int getCount() const { return count; }

    void findByType(const char* searchType) const {
        cout << "Водойми типу '" << searchType << "':" << endl;
        bool found = false;
        for (int i = 0; i < count; i++) {
            Reservoir temp;
            temp.setType(searchType);
            if (reservoirs[i].isSameType(temp)) {
                cout << "\n" << i + 1 << ". ";
                reservoirs[i].displayInfo();
                found = true;
            }
        }
        if (!found) {
            cout << "Водойм цього типу не знайдено" << endl;
        }
    }

    void compareReservoirs(int index1, int index2) const {
        if (index1 < 0 || index1 >= count || index2 < 0 || index2 >= count) {
            cout << "Неправильні індекси!" << endl;
            return;
        }

        const Reservoir& r1 = reservoirs[index1];
        const Reservoir& r2 = reservoirs[index2];

        cout << "Порівняння водойм:" << endl;
        cout << "1. " << r1.getName() << " (" << r1.getType() << ")" << endl;
        cout << "2. " << r2.getName() << " (" << r2.getType() << ")" << endl;

        if (!r1.isSameType(r2)) {
            cout << "Водойми різних типів, порівняння неможливе" << endl;
            return;
        }

        double area1 = r1.calculateSurfaceArea();
        double area2 = r2.calculateSurfaceArea();

        cout << "Площа поверхні 1: " << area1 << " м²" << endl;
        cout << "Площа поверхні 2: " << area2 << " м²" << endl;

        if (area1 > area2) {
            cout << "Водойма 1 більша за площею" << endl;
        } else if (area1 < area2) {
            cout << "Водойма 2 більша за площею" << endl;
        } else {
            cout << "Водойми мають однакову площу" << endl;
        }
    }

    void saveToTextFile() const {
        cout << "=== ЗБЕРЕЖЕННЯ У ТЕКСТОВИЙ ФАЙЛ ===" << endl;
        cout << "Кількість водойм: " << count << endl;
        for (int i = 0; i < count; i++) {
            cout << "Водойма " << i + 1 << ":" << endl;
            cout << reservoirs[i].getName() << " " << reservoirs[i].getType() << " "
                 << reservoirs[i].getWidth() << " " << reservoirs[i].getLength() << " "
                 << reservoirs[i].getMaxDepth() << endl;
        }
    }

    void saveToBinaryFile() const {
        cout << "=== ЗБЕРЕЖЕННЯ У БІНАРНИЙ ФАЙЛ ===" << endl;
        cout << "Дані для бінарного файлу (імітація):" << endl;
        cout << "Count: " << count << endl;
        for (int i = 0; i < count; i++) {
            cout << "Record " << i << ": " << reservoirs[i].getName() << endl;
        }
    }
};

void showMenu() {
    cout << "\n=== МЕНЮ УПРАВЛІННЯ ВОДОЙМАМИ ===" << endl;
    cout << "1. Додати водойму" << endl;
    cout << "2. Видалити водойму" << endl;
    cout << "3. Показати всі водойми" << endl;
    cout << "4. Знайти водойми за типом" << endl;
    cout << "5. Порівняти дві водойми" << endl;
    cout << "6. Копіювати водойму" << endl;
    cout << "7. Зберегти у текстовий файл" << endl;
    cout << "8. Зберегти у бінарний файл" << endl;
    cout << "0. Вийти" << endl;
    cout << "Оберіть опцію: ";
}

int main() {
    ReservoirArray reservoirArray;
    int choice;

    cout << "Система управління водоймами" << endl;

    while (true) {
        showMenu();
        cin >> choice;

        switch (choice) {
            case 1: {
                char name[MAX_NAME_SIZE], type[MAX_NAME_SIZE];
                double width, length, depth;

                cout << "Введіть назву водойми: ";
                cin >> name;
                cout << "Введіть тип (Озеро/Море/Басейн/Ставок): ";
                cin >> type;
                cout << "Введіть ширину (м): ";
                cin >> width;
                cout << "Введіть довжину (м): ";
                cin >> length;
                cout << "Введіть максимальну глибину (м): ";
                cin >> depth;

                Reservoir newReservoir(name, type, width, length, depth);
                reservoirArray.addReservoir(newReservoir);
                break;
            }

            case 2: {
                int index;
                cout << "Введіть номер водойми для видалення (1-" << reservoirArray.getCount() << "): ";
                cin >> index;
                reservoirArray.removeReservoir(index - 1);
                break;
            }

            case 3: {
                reservoirArray.displayAll();
                break;
            }

            case 4: {
                char searchType[MAX_NAME_SIZE];
                cout << "Введіть тип для пошуку: ";
                cin >> searchType;
                reservoirArray.findByType(searchType);
                break;
            }

            case 5: {
                int index1, index2;
                cout << "Введіть номер першої водойми: ";
                cin >> index1;
                cout << "Введіть номер другої водойми: ";
                cin >> index2;
                reservoirArray.compareReservoirs(index1 - 1, index2 - 1);
                break;
            }

            case 6: {
                int sourceIndex;
                cout << "Введіть номер водойми для копіювання: ";
                cin >> sourceIndex;
                
                Reservoir* source = reservoirArray.getReservoir(sourceIndex - 1);
                if (source != nullptr) {
                    Reservoir copy(*source);
                    char newName[MAX_NAME_SIZE];
                    cout << "Введіть нову назву для копії: ";
                    cin >> newName;
                    copy.setName(newName);
                    reservoirArray.addReservoir(copy);
                } else {
                    cout << "Неправильний індекс!" << endl;
                }
                break;
            }

            case 7: {
                reservoirArray.saveToTextFile();
                break;
            }

            case 8: {
                reservoirArray.saveToBinaryFile();
                break;
            }

            case 0: {
                cout << "До побачення!" << endl;
                return 0;
            }

            default: {
                cout << "Неправильний вибір!" << endl;
                break;
            }
        }
    }

    return 0;
}
