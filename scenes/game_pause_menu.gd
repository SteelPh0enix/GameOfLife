extends VBoxContainer

signal exit_pressed
signal continue_pressed


func _on_continue_button_pressed() -> void:
	continue_pressed.emit()


func _on_exit_button_pressed() -> void:
	exit_pressed.emit()
