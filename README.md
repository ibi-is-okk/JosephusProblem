# **Josephus Problem Visualization** 🎮

This is a **C++** program that visualizes the **Josephus Problem** using **SFML** (Simple and Fast Multimedia Library). The Josephus Problem is a famous theoretical problem related to a certain elimination game where every `k`-th person is eliminated in a circle until only one person remains.

---

## **Overview** 🕹️

In this program, the soldiers are arranged in a circle, and every `k`-th soldier is eliminated in turn. The program uses the **SFML graphics library** to display the soldiers as green circles and updates the visualization by changing the color of the eliminated soldier to **red**.

---

## **Features** ✨

- **Visualization:** Each soldier is represented by a circle, and the elimination process is visually shown.
- **Interactive:** Press the **space bar** to eliminate the `k`-th person and visualize the change.
- **Real-time Updates:** The screen is updated to reflect the elimination of soldiers in the circle.

---

## **How to Play** 🕹️

1. **Run the Program:**
   - Compile and run the C++ program that uses the SFML library.
   - Enter the total number of soldiers and the step `k` for the elimination process.

2. **Controls:**
   - **Space Bar:** Eliminate the `k`-th soldier from the circle and update the display.

3. **Objective:**
   - The goal is to visualize and step through the elimination process, where each soldier is eliminated until only one remains.

---

## **Code Breakdown** 📜

### **JosephusProblem Class**

1. **`JosephusProblem(int maxSize)` Constructor:**
   - Initializes the array of soldiers and sets up the number of people, front position, and count.

2. **`~JosephusProblem()` Destructor:**
   - Deletes the dynamic array of soldiers.

3. **`killPerson()` Method:**
   - Marks the current soldier for elimination by setting their value to `-1` and decreases the count.

4. **`getNextAlive(int step)` Method:**
   - Finds the next soldier alive by stepping `k` positions in the circle.

5. **`getFront()` Method:**
   - Returns the ID of the current soldier at the front of the circle.

6. **`setFront(int index)` Method:**
   - Sets the current position of the front soldier.

---

### **Main Program Logic**

1. **SFML Setup:**
   - Initializes the SFML window and sets up a circle for each soldier.

2. **Event Handling:**
   - Listens for the **space bar** to eliminate the `k`-th soldier and updates the visualization.

3. **Circle Drawing:**
   - For each soldier, a circle is drawn and displayed. The eliminated soldiers are marked in **red**.

4. **Termination:**
   - The program continues until the window is closed.

---



## **How to Build and Run** 🚀

1. **Install SFML:**
   - Download and install the SFML library from [SFML Downloads](https://www.sfml-dev.org/download.php).

2. **Compile the Program:**
   - Use the following commands to compile and link your program with the SFML library:
   ```bash
   g++ -o josephus game.cpp -lsfml-graphics -lsfml-window -lsfml-system
