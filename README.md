# Sale Tracker Retro
**AUTHOR . . . . . . .** Shahar Ankonina                                                                                     
**DESCRIPTION. . .** A desktop sale tracking application built in C++ using SFML, featuring dynamic item management, interactive UI controls, real-time total calculations, and custom scrollable views

---
## About
Sale Tracker is a desktop GUI application originally built for the local theater company **GIFT** to assist with small bake sales. Developed in C++ using SFML, the architecture is modular and object-oriented, featuring custom UI components like interactive buttons, editable text boxes, price-formatted inputs, and a dynamic scrollbar.

The application handles dynamic memory management for user-created elements, computes real-time total sales revenue, and supports audio feedback such as click and keyboard sound effects during user interaction.

---
## Features
- *Dynamic Item Management:* Add new sale items on the fly, with custom name editing and price parsing.
- *Interactive UI Controls:* Polished buttons for selling (`+$`), unselling (`-$`), and removing items entirely, alongside responsive text fields and a scrollable viewport.
- *Real-Time Totals:* Automatically calculates total revenue by multiplying sold quantities by item prices.
- *Custom Scrollable View:* Seamlessly navigate through items using mouse wheel scrolling and a custom scrollbar track.
- *Audio & Visual Feedback:* Integrated sound effects for clicks and keyboard input, complete with hover and pressed visual states.

---
## Tech Stack
- *Programming Languages:* C++
- *Libraries & Frameworks:* SFML (Simple and Fast Multimedia Library) for graphics, window handling, audio, and view management
- *Tools & Platforms:* Visual Studio, Git/GitHub

---
## Usage
- This project is a desktop application built with SFML.
- Open the application window, click the **"ADD ITEM"** button to create a new row, click into the text or price fields to edit details, and use the sale buttons to update quantities.
- Ensure asset folders (`Assets\\Fonts\\`, `Assets\\Sounds\\`, `Assets\\Sprites\\`) remain accessible relative to the executable path so textures, fonts, and audio files load correctly.

### Build & Run
Requires a C++ compiler set up with SFML. On Windows, open the solution file or project structure in Visual Studio, configure the build settings to match your SFML environment, and build/run the project.

*(Note: A prebuilt executable is also included in the repository folder for quick testing).*

- Explore the codebase (`ScreenManager`, `Item`, `Button`, `TextBox`) to see how modular, object-oriented GUI components are structured using SFML.
