extends Control


var tcp_server :TCPServer = TCPServer.new()
var connection_prise :bool = false
var stream : StreamPeerTCP
var data :String = ''

var sensors_value :Array [float] = [.0,.0,.0]

const taux_echantillonnage_multiplier :int = 10 #60/nbr_capteur *tem

var sensors_name :Array[String] = ['H', 'S', 'V','R','G','B','FPS']
# Called when the node enters the scene tree for the first time.
func _ready():
	tcp_server.listen(4444,"127.0.0.1")


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	#print(tcp_server.is_connection_available())
	if tcp_server.is_connection_available() and not connection_prise :
		stream = tcp_server.take_connection()
	
	if stream != null :
		var read_char :String = ''
		for i in range(taux_echantillonnage_multiplier):
			read_char = stream.get_string(1)
			if read_char != ";" :
				data += read_char
			else :
				print(data)
				var data_array :PackedStringArray = data.right(-1).split(' ')
				print(data_array)
				var sensor_int :int = sensors_name.bsearch(data_array[0])
				if not sensor_int == 3 :
					sensors_value[sensor_int] = float(data_array[1])
				print(sensors_value)
				data = ""
				#var value :float  = float(data.split(' ')[1])
				#var sensor :String =  data.split(' ')[0]
	var compte = 1
	for val in sensors_value :
		$ColorRect.material.set_shader_parameter("param"+str(compte),val)
		compte += 1
