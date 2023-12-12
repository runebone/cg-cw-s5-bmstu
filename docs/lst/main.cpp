int main() {
    Engine engine;
    engine.initialize();

    while (engine.isRunning()) {
        engine.processInput();
        engine.update();
        engine.render();
    }
    // ...
}
