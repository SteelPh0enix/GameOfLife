extends Node

var scene_stack: Array[PackedScene] = []

func change_scene(scene_path: String) -> void:
	if get_tree().current_scene:
		var packed_scene = PackedScene.new()
		var packing_result = packed_scene.pack(get_tree().current_scene)
		assert(packing_result == OK, "Couldn't add current scene to scene manager's stack!")
		scene_stack.push_back(packed_scene)

	get_tree().change_scene_to_file(scene_path)

func go_back() -> void:
	var previous_scene = scene_stack.pop_back()
	assert(previous_scene, "Couldn't fetch previous scene from scene manager's stack!")
	get_tree().change_scene_to_packed(previous_scene)
