# C++ Design Pattern Project

This project explores and demonstrates the implementation of various C++ design patterns, inspired by concepts found in games like League of Legends.

## Project Analysis

# C++ Design Pattern Project Analysis

This project demonstrates the implementation and application of several GoF (Gang of Four) design patterns in C++, primarily focusing on the **Facade** and **Visitor** patterns. The project is structured into a main directory containing standalone examples of these patterns and a `game` subdirectory that integrates them into a simple game context.

## I. Standalone Design Pattern Examples

### 1. Facade Pattern
The Facade pattern provides a simplified interface to a complex subsystem. It hides the complexities of the system and presents a more user-friendly interface to the client.

*   **`facade.cpp`**: This file contains a more complete example of a `CraftingFacade`.
    *   **Subsystem Classes**:
        *   `Item`: Represents individual items with attributes like ID, name, bonus ATK, and bonus HP.
        *   `CraftingRecipe`: Defines the components required to craft a specific `Item`. It manages the logic for checking if an item can be crafted and performing the crafting process by consuming items from an inventory.
    *   **Facade (`CraftingFacade`)**: Offers a high-level interface for crafting and inventory management.
        *   `craftItem(itemName)`: Initiates the crafting of a specified item.
        *   `displayInventory()`: Shows the current contents of the inventory.
        *   `addItem(itemName, amount)`: Adds a specified quantity of an item to the inventory.
        *   `removeItem(itemName, amount)`: Removes a specified quantity of an item from the inventory.
    *   **Benefits**: The client (main function) interacts only with `CraftingFacade`, abstracting away the intricacies of `Item` and `CraftingRecipe` management.

*   **`FacadeExample.cpp`**: A simpler illustration of the Facade pattern using a food delivery service.
    *   **Subsystem Classes**: `Dish`, `Restaurant`, `Order`, `Customer`, `Driver`. Each class handles a specific aspect of the food delivery process.
    *   **Facade (`FoodDeliveryFacade`)**: Simplifies the process of placing a food order. It coordinates interactions between the `Customer`, `Restaurant`, and `Driver` to `placeOrder()`.
    *   **Benefits**: The `FoodDeliveryFacade` allows a client to place an order with a single call, without needing to know the complex steps involving multiple components.

### 2. Visitor Pattern
The Visitor pattern allows adding new operations to a set of objects without changing the objects' structure. It involves a "visitor" object that performs the operation and "element" objects that accept the visitor.

*   **`visitor.cpp`**: Demonstrates the Visitor pattern in a basic game interaction scenario.
    *   **Element Hierarchy**:
        *   `Element` (base class): Defines the `Interact(Visitor *v)` method.
        *   `Entity`: Derived from `Element`, representing game entities.
        *   `Player`, `Foe`, `Terrain`: Concrete element classes, each implementing `Interact` to call the appropriate method on the visitor.
    *   **Visitor Hierarchy**:
        *   `Visitor` (abstract base class): Declares `InteractPlayer`, `InteractFoe`, `InteractTerrain` methods.
        *   `ScanVisitor`: A concrete visitor that performs information display (scanning) on game elements.
        *   `AttackVisitor`: A concrete visitor that performs attack/damage operations on game elements.
    *   **Benefits**: New interaction types (e.g., `HealVisitor`, `BuffVisitor`) can be added by creating new concrete `Visitor` classes without modifying the `Element` classes.

*   **`VisitorExample.cpp`**: Illustrates the Visitor pattern in an environmental data analysis context.
    *   **Element Hierarchy**: `Environment` (base class), `Forest`, `Coastal`, `Desert` (concrete environment types).
    *   **Visitor Hierarchy**: `Visitor` (abstract base class), `GetInfoVisitor`, `CheckStateVisitor`.
    *   **Benefits**: Allows different types of analyses (getting info, checking state) to be performed on various environment types by distinct visitor objects.

## II. Integrated Game Project (`game` directory)

The `game` subdirectory showcases a more comprehensive application of these design patterns within a simple game framework.

### 1. Design Patterns Used

*   **Visitor Pattern (Extensive)**: Central to handling combat and entity interactions.
    *   **Elements**: `Entity` serves as the base, with derived classes `Player`, `NormalFoe`, `EpicFoe`, and `BossFoe`. Each entity implements an `Interact(Visitor *v)` method.
    *   **Visitors**:
        *   `Visitor` (abstract): Defines interaction methods for each concrete entity type.
        *   `AttackVisitor`: Manages attack logic, tracks battle points, and applies damage.
        *   `HealVisitor`: Handles healing logic and applies health restoration.
        *   `InfoVisitor`: Displays detailed information about entities.
        *   `InteractiveVisitors`: A composite class encapsulating instances of `AttackVisitor`, `HealVisitor`, and `InfoVisitor` for convenient use in game logic.
    *   **Usage**: The `TakeAction` methods (for both players and foes) and specific attack/heal methods (`SingularAttack`, `HealTarget`) leverage these visitors, enabling polymorphic interactions.

*   **Facade Pattern (for Crafting/Shop)**:
    *   **Subsystem**: The `Crafting.h` and `Crafting.cpp` files define the `Item` and `CraftingRecipe` classes.
    *   **Facade (`CraftingFacade`)**: Provides a simplified interface for buying, crafting, and selling items within the game's shop (`Game::ShopnCraft` function). It abstracts the complexities of managing item lists, recipes, and inventory modifications from the main game loop.

### 2. Game Features and Technical Implementation

*   **Core Entities (`Entity.h`, `Entity.cpp`)**:
    *   **Base Class `Entity`**: Attributes include `name`, `baseHP`, `baseATK`, `currentHP`, `state` (alive/dead), and `buffATK`.
    *   **Polymorphic Behavior**: Virtual functions such as `getATK()`, `getHP()`, `Interact()`, `Attacked()`, `Healed()`, `SingularAttack()`, `HealTarget()`, `ShowInfo()`, `ResetState()`, and `TakeAction()` allow for diverse behaviors among different entity types.
    *   **Player Class**: Manages an `inventory` (an `unordered_map<Item*, int>`), calculates `itemsATK` and `itemsHP` bonuses from equipped items.
    *   **Foe Classes (`NormalFoe`, `EpicFoe`, `BossFoe`)**: Each has specialized behaviors:
        *   `NormalFoe`: Can `Flee()` when low on health.
        *   `EpicFoe`: Incorporates a `fury` mechanic, getting stronger or healing based on damage taken. Can perform `SpecialAttack`.
        *   `BossFoe`: Features `progress` states, allowing it to "transform" (gain HP/ATK) or `spawn minions` when its health drops. Can perform `SpecialAttack`.

*   **Combat System (`Combat.h`, `Combat.cpp`)**:
    *   The `Game::Combat` function orchestrates turn-based battles between players and enemies.
    *   It manages entity states, handles turn progression, and checks for win/loss conditions.
    *   Player input for actions (Attack, Heal, Take Info, Skip) is handled within `Player::TakeAction`.
    *   Foe AI is implemented in `Foe::TakeAction` and its derivatives, utilizing random actions and visitor patterns for effects.
    *   Includes dynamic management of `dead_enemies` and `dead_players` to correctly update combat participants.

*   **Crafting & Shop System (`Crafting.h`, `Crafting.cpp`, `Game::ShopnCraft`)**:
    *   `Item`s have `id`, `name`, `bonusATK`, `bonusHP`.
    *   `CraftingRecipe`s define which items are needed to craft a `resultItem`. Base items have `nullptr` in their `requiredItems`.
    *   `CraftingFacade` simplifies interactions, allowing players to `addItem`, `craftItem`, and `displayInventory`. `initializeCraftingRecipes` sets up a static list of all possible items and their recipes.
    *   The `Game::ShopnCraft` function integrates this facade, allowing players to spend `gold` to `Buy` basic items or `Craft` advanced items.

*   **Main Game Loop (`game/main.cpp`)**:
    *   Initializes `Player` objects and the `Game` object.
    *   Presents a main menu to the user: `FIGHT!!!`, `Shop n' craft`, or `Quit`.
    *   The `Game` class manages the overall game state, including `gold` and `level`.

## III. Overall Architecture and Conventions

The project demonstrates a well-organized structure using object-oriented principles and design patterns.
*   **Separation of Concerns**: Each pattern (Facade, Visitor) and core game component (Combat, Crafting, Entity) is modular, promoting maintainability and extensibility.
*   **Polymorphism**: Extensively used in the `Entity` hierarchy and `Visitor` interactions to allow for flexible and diverse behaviors without modifying core structures.
*   **Encapsulation**: Details of complex operations (e.g., crafting recipes, entity damage calculation) are hidden behind simpler interfaces (Facade) or handled by specialized objects (Visitors).
*   **Code Style**: Uses standard C++ practices, `using namespace std;`, and includes necessary headers. Comments are used to explain parts of the code.

This project serves as a good example of applying common design patterns to build a structured and extensible C++ application, particularly in a game development context.
