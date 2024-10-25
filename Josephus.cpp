#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
using namespace std;
using namespace sf;

const float PI = 3.14159265358979323846;

class JosephusProblem {
private:
    int* people;
    int front;
    int numberOfPeople;
    int count;

public:
    JosephusProblem(int maxSize) : numberOfPeople(maxSize), front(0), count(maxSize) {
        people = new int[numberOfPeople];
        for (int i = 0; i < numberOfPeople; i++) {
            people[i] = i + 1;
        }
    }

    ~JosephusProblem() {
        delete[] people;
    }

    void killPerson() {
        if (count > 0) {
            people[front] = -1;
            count--;
        }
    }

    void getNextAlive(int step) {
        int x = 0; // count of ppl alive
        while (x < step) { // step -1 nxt alive person
            if (people[front] != -1) {
                x++;
            }
            if (x < step) {
                front = (front + 1) % numberOfPeople; 
            }
        }
    }

    int getFront() {
        return people[front];
    }
    int getCount() const {
        return count;
    }
    void setFront(int index) {
        front = index;
    }
};

int main() {
    int numSol = 0;  
    int k = 0;        

    cout << "\n\tEnter number of soldiers : ";
    cin >> numSol;
    cout << "\tEnter k : ";
    cin >> k;
    JosephusProblem SOLDIERS(numSol);

    RenderWindow window(VideoMode(1000, 1000), "Josephus Problem Visualization");
    window.setFramerateLimit(10);
    float radius = 300.0f;     
    float centerX = 500.0f; 
    float centerY = 500.0f; 
    CircleShape* circles = new CircleShape[numSol];

    for (int i = 0; i < numSol; ++i) { //  circle for each person
        float angle = (2 * PI / numSol) * i; 
        float x = centerX + radius * cos(angle);
        float y = centerY + radius * sin(angle);

        circles[i].setRadius(15.0f);
        circles[i].setFillColor(Color::Green);  
        circles[i].setPosition(x - circles[i].getRadius(), y - circles[i].getRadius());
    }

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Space && SOLDIERS.getCount() > 1) {
                SOLDIERS.getNextAlive(k);
                cout << "\tkilled : " << SOLDIERS.getFront() << endl;
                circles[SOLDIERS.getFront() - 1].setFillColor(Color::Red);
                SOLDIERS.killPerson();  
            }
        }
        window.clear();
        for (int i = 0; i < numSol; ++i) {
            window.draw(circles[i]);
        }
        window.display();
    }
    delete[] circles;
}
