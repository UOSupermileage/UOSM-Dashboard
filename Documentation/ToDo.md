# ToDo List

## 1. Bar chart that displays lap efficiencies.

- Create a bar chart that visualizes lap efficiencies.
- Each lap trigger event can be mocked with a button on the screen for now.
- Each lap should appear as a new bar on the chart.
- Color code each bar based on the lap efficiency, with the most efficient lap in green and the least efficient in red.
- Recompute the colors of the bars every time a new lap is added.
- The y-axis scale should be dynamic, with the most efficient lap represented as 100%.
- Utilize a percentage-based y-axis to maximize screen space.

## 2. Large format efficiency number percentage.

- Implement a reusable view for the large format efficiency number percentage.
- The view should accept an Observable object to listen to and display its value.
- It will display the value provided by the Observable object.

## 3. Graph of RPM, Current, Voltage, Throttle over time.

- Create an interactive graph that plots RPM, Current, Voltage, and Throttle over time.
- Compute a percentage for each value based on its highest possible value.
- Display the percentages in the graph to allow multiple values to share a y-axis.
- Provide a legend to display the current value units (RPM, A, V, etc.) for user reference.
- Include a checkbox system to toggle the visibility of each value in the graph.
- Assign a different color to each line representing a value.

## 4. Large format lap time.

- Implement a reusable view for the large format lap time display.
- The view should accept an Observable object to listen to and display the lap time.
- It will display the lap time value provided by the Observable object.

## 5. Easily change the default screen at compile time.

- Use #define to specify the order in which the screens appear.
- This approach will enable easy changes to the default screen by modifying the compilation options.

---

**Note:** Throughout the project, keep flexibility in mind to ensure the system remains highly adaptable and easy to
customize for different use cases.

