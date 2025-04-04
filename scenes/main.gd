extends Node

func set_minimum_window_size() -> void:
	var viewport_width = ProjectSettings.get("display/window/size/viewport_width")
	var viewport_height = ProjectSettings.get("display/window/size/viewport_height")
	get_window().set_min_size(Vector2i(viewport_width, viewport_height))

func _ready() -> void:
	print("Hello, world!")
	set_minimum_window_size()

func _on_exit_button_pressed() -> void:
	print("Quitting the application...")
	get_tree().root.propagate_notification(NOTIFICATION_WM_CLOSE_REQUEST)
	get_tree().quit()

func _on_start_game_button_pressed() -> void:
	print("Starting new game...")
	SceneManager.change_scene("res://scenes/game_board.tscn")
