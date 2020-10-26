from Score_Server import *

#Dictionnaire contenant toutes les commandes et les fonction associe
command = {
	"help" :	[1, """self.openRead("help.txt")"""],
	"status" :	[1, "print(self.score_server.getStatus())"],
	"exit" :	[1, "self.exit()"],
	"start" :	[2, "self.start(self.{})"],
	"stop" :	[2, "self.stop(self.{})"],
	"verbose" :	[3, "self.set_verbose(self.{},{})"]
}

#Dictionnaire contenant tous les serveurs et leur variable associe
servers = {
	"game" :		"game_server",
	"Game" :		"game_server",
	"gameserver" :	"game_server",
	"score" :		"score_server",
	"Score" :		"score_server",
	"scoreserver" :	"score_server"
}

#Dictionnaire contenant tous les arguments et leur valeur associe
arguments = {
	"on" :		True,
	"On" :		True,
	"ON" :		True,
	"off" :		False,
	"Off" :		False,
	"OFF" :		False
}




class ServerManager():
	"""Lis les entrees du terminal et effectue les actions necessaire"""

	def __init__(self):
		"Creer l'objet"
		self.running = True
		self.score_server = ScoreServer()

	def processCommand(self,str):
		"Do the action required by the string str"

		#Ne fait rien si str est vide
		if str != "":
			line = str.split()

			#Verifie si la ligne est valide et une commande
			if len(line) != 0 and line[0] in command:
				cmd = command.get(line[0])

				#Si le nombre d'argument est bon
				if cmd[0] == len(line):
					if len(line) == 1:
						#Execute la commande associee
						exec(cmd[1])

					else:
						#Verifie que le serveur soit valide
						if line[1] in servers:
							serv = servers.get(line[1])
							#Si le nombre d'argument est bon
							if len(line) == 2:
								#Execute la commande associee
								exec(cmd[1].format(serv))
							else :
								#Verifie que l'argument soit valide
								if line[2] in arguments:
									arg = arguments.get(line[2])
									#Si le nombre d'argument est bon
									if len(line) == 3:
										#Execute la commande associee
										exec(cmd[1].format(serv,arg))
								else :
									print("Unknown argument")

						else :
							print("Unknown server.")
				else :
					print("Wrong number of arguments.")
			else :
				print("Unknown command type help to see all the command.")


	def openRead(self,filename):
		"Ouvre un fichier et l'ecrit sur le terminal"
		f = open(filename,"r")
		for line in f:
			print(line,end= "")
		f.close()

	def isRunning(self):
		"Dis si le serveur est en marche"
		return(self.running)

	def exit(self):
		"Ferme tout les serveurs et arrete le programme"
		print("Close everything")
		self.score_server.stop()
		self.running = False

	def start(self,server):
		"Demarre le serveur"
		if  not server.isRunning() :
			print("Starts {} server".format(server.getName()))
			server.start()
		else :
			print("Cannot start {} server".format(server.getName()))


	def stop(self,server):
		"Stop le serveur"
		if server.isRunning():
			server.stop()	#Demande au serveur de s'arreter
			server.join()	#Termine le thread
			self.score_server = ScoreServer()	#Creer un nouveau thread
		else :
			print("Cannot stop {} server".format(server.getName()))

	def set_verbose(self,server,arg):
		"Set the verbose of the server"
		if server.isRunning():
			server.set_verbose(arg)
			print("Verbose was sucessfully set on {} server".format(server.getName()))
		else :
			print("Cannot set verbose on {} server".format(server.getName()))


mainServer = ServerManager()

while mainServer.isRunning() :
	inp = input(">>> ")
	mainServer.processCommand(inp)
