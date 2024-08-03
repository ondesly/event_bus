# event bus
A lightweight and fast event bus based on monostate pattern

## Usage
1. Define event
 ```cpp
struct event_t {
    int value = 0;
};
```

2. Add listener
```cpp
auto listener = ev::bus{}.listen([](const event_t &event) {
    std::cout << "event: " << event.value << std
});
```

3. Dispatch event
```cpp
ev::bus{}.dispatch(event_t{5});
```

4. Process changes
```cpp
ev::bus{}.process();
```

## Requirements

This library requires a C++17 compiler and standard library.
