import os, sys, time

if __name__ == "__main__":
	
	time.sleep(3)
	#strings get written here
	#opening mkfifo
	firstFile = "./files/firstFile"
	pipe = open(firstFile,"r")
	receivedString2 = pipe.readline();
	receivedString = pipe.readline();
	os.remove(firstFile)
	newString = ""
	
	htmlFilename = receivedString2
	htmlFilename = htmlFilename[0:len(htmlFilename)-1]
	htmlFilename += ".html"
	
	htmlFile = open(htmlFilename, "w")
	
	htmlFile.write("<HTML>\n")
	htmlFile.write("<HEAD>\n")
	htmlFile.write("<TITLE>\n")
	htmlFile.write(receivedString2)
	htmlFile.write("</TITLE>\n")
	htmlFile.write("</HEAD>\n")
	htmlFile.write("<BODY>\n")
	
	infoFilename = receivedString2
	infoFilename = infoFilename[0:len(infoFilename)-1]
	infoFilename += ".info"
	
	#check to see if info file exists
	if(os.path.isfile(infoFilename)):
		#I think ill loop until EOF, reading each line in and processing old strings to add HTML tags
		with open(infoFilename, "r") as infoFile:
			for infoString in infoFile:
				try:
					infoString = infoString[0:len(infoString)-1]
				
					newString = ""
				
					newString += '<'
					newString += infoString[0]
					newString += '>'
					newString += infoString[2:(len(infoString))]
					newString += '</'
					newString += infoString[0]
					newString += '>'
			
					receivedString = receivedString.replace(infoString[2:len(infoString)], newString)
				except:
					pass
	
		
	#piping back to c
	
	
	secondFile = "./files/secondFile"
	time.sleep(2)
	pipe = os.open(secondFile, os.O_WRONLY)
	os.write(pipe, "<HTML>\n")
	os.write(pipe, "<HEAD>\n")
	os.write(pipe, "<TITLE>\n")
	os.write(pipe, receivedString2)
	os.write(pipe, "</TITLE>\n")
	os.write(pipe, "</HEAD>\n\n")
	os.write(pipe, "<BODY>\n")
	os.write(pipe, receivedString)
	os.write(pipe, "\n")
	os.write(pipe, "</BODY>\n")
	os.write(pipe, "</HTML>")
	os.close(pipe)
	
	htmlFile.write(receivedString)
	htmlFile.write("\n")
	
	htmlFile.write("</BODY>\n")
	htmlFile.write("</HTML>")
	htmlFile.close()
