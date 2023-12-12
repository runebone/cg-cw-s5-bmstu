class GameState {
public:
    static GameState& get() {
        static GameState instance;
        return instance;
    }
    // ...
    std::shared_ptr<Camera> getCamera() const;
    std::shared_ptr<Scene> getScene() const;
    std::shared_ptr<GameObject> getSelectedObject() const;
    // ...
};
