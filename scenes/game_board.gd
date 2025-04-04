extends Node

enum GameState {
    PAUSED,
    RUNNING,
}

var game_state: GameState = GameState.PAUSED
var pause_menu: Control

func pause_game() -> void:
    print("Pausing the game...")
    game_state = GameState.PAUSED
    pause_menu.visible = true

func resume_game() -> void:
    print("Resuming the game...")
    pause_menu.visible = false
    game_state = GameState.RUNNING

func end_game() -> void:
    print("Ending the game...")
    game_state = GameState.PAUSED

func _ready() -> void:
    pause_menu = get_node("GamePauseMenu")
    resume_game()

func _on_game_pause_menu_continue_pressed() -> void:
    resume_game()

func _on_game_pause_menu_exit_pressed() -> void:
    end_game()
    SceneManager.go_back()

func _process(_delta: float) -> void:
    if Input.is_action_just_pressed("pause_game"):
        if pause_menu.visible:
            resume_game()
        else:
            pause_game()
