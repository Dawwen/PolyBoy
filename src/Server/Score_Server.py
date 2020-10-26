import socket
import os
import datetime
from threading import Thread

class ScoreRequete:
	"""Classe requete recoit et traite les requetes"""
	def __init__(self,line,client):
		self.value = False

		if (line == ""):
			self.msg = "Pas de requete\n"
			return
		tmp = line.split()

		#Si c'est une commande pour recevoir la date
		if  len(tmp) == 2 and tmp[1].decode() == "date":
			self.READ = True
			self.game = tmp[1].decode()
			self.key = 55
			self.client = client
			self.value = True
			return

		if len(tmp) != 5:
			self.msg = "Mauvais nombre d'argument\n"
			return

		if not os.path.isfile(tmp[1].decode() + ".data"):
			self.msg = "Jeu non reconnu\n"
			return

		#Demande la lecture de donnee sur le serveur
		if tmp[0].decode() == "READ":
			self.value = True
			self.READ = True

			self.game = tmp[1].decode()
			self.start = int(tmp[2].decode())
			self.end = int(tmp[3].decode())
			self.key = int(tmp[4].decode())

			self.client = client

		#Demande l'ecriture de donne sur le serveur
		elif tmp[0].decode() == "WRITE":
			self.value = True
			self.READ = False

			self.game = tmp[1].decode()
			self.name = tmp[2].decode()
			self.score = int(tmp[3].decode())
			self.key = int(tmp[4].decode())

			self.client = client

		else :
			self.msg = "Commande non reconnu\n"

	def readScoreboard(self):
		"Lis le fichier de score associe"
		self.msg = ""
		f = open(self.game + ".data","r")
		i = 1
		for line in f:
			if (i >= self.start and i <= self.end):
				self.msg = self.msg + line
			i += 1
		f.close()

	def readDate(self):
		"Lis la date"
		now = datetime.datetime.now()
		self.msg = "{}, {}, {}, {}, {}".format(now.day,now.month,now.year,now.hour,now.minute)

	def writeScore(self):
		"Rajoute le score au fichier associe"
		f = open(self.game + ".data","r")
		tmp = f.readlines()
		f.close()

		write = False
		f = open(self.game + ".data","w")
		for line in tmp:
			a = line.split()
			if (not write and int(a[1]) < self.score):
				write = True
				f.write(self.name + " " + str(self.score) + "\n")
			f.write(line)
		if (not write):
			f.write(self.name + " " + str(self.score) + "\n")
		f.close()
		self.msg = "Score marque"

	def work(self):
		"Effectue le travail demande par la requete"
		if (self.READ):
			if self.game != "date" :
				self.readScoreboard()
			else :
				self.readDate()
		else :
			self.writeScore()



	def sendMsg(self):
		"Renvoie le message"
		try :
			self.client.send(self.msg.encode())
		except OSError as msg:
			print("Client non joignable")

	def getLengthMsg(self):
		"Donne la longueur du message"
		return(len(self.msg))



class ScoreServer(Thread):
	"""Thread chargé simplement d'afficher une lettre dans la console."""

	def __init__(self):
		Thread.__init__(self)
		self.name = "Scoreboard"
		self.verbose = False
		self.running = False

	def run(self):
		"""Code à exécuter pendant l'exécution du thread. Executer automatiquement apres le start()"""

		self.running = True
		#Creer le server TCP/IP
		self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		self.socket.bind(('', 1234))

		while self.running:
			#Ecoute pour les requetes
			self.socket.listen(5)
			client, address = self.socket.accept()

			if self.running :
				self.s_print("\n###################\nSCORE_SERVER\n###################")
				self.s_print("{} connected".format( address ))

				#Lis le messge recu
				response = client.recv(255)
				#Creer la requete associe
				req = ScoreRequete(response, client)
				self.s_print(response.decode())

				#Si la requete est valide
				if (req.value):
					#Effectue le requete et repond au client
					req.work()
					req.sendMsg()

					client.sendall(req.key.to_bytes(1, byteorder='big'))
				else :
					client.sendall(req.msg.encode())
					client.sendall("END\n".encode())
				client.close()
				self.s_print("###################\nFIN SCORE_SERVER\n###################\n>>","")

		print("Closed ScoreBoard server")
		#ferme le serveur TCP/IP
		self.socket.close()

	def s_print(self,msg, end = "\n"):
		"Affiche seulement si verbose est actif"
		if self.verbose:
			print(msg, end)

	def getName(self):
		return(self.name)

	def getStatus(self):
		"Renvoie l'etat du serveur"
		out = "ScoreBoard Server : "
		if self.running:
			out += "On"
		else :
			out += "Off"
		return(out)

	#def stop(self):
	#	self.running = False
	#	self.stock.close()

	def stop(self):
		"Stop le serveur"
		if self.running:
			self.running = False
			socket.socket(socket.AF_INET,
					socket.SOCK_STREAM).connect( ("127.0.0.1", 1234))
			#self.socket.close()

	def set_verbose(self,bol):
		self.verbose = bol

	def isRunning(self):
		return(self.running)
