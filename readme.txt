README.TXT
------------------------------------------------------
Name: Alexander Sadakhom

This project utilizes code that has been built and added to throughout a semester. First it started with just a simple C program that took in a text file and formatted it. It did this by removing unnecessary extra spaces, tabs and line skips (\n in c). 

From there we added fifo piping to and from python. The program would read the file in c, format the text document, and then pipe the text over to a python script for further modifications. The python script would read in a separate file than the text document that would specify words that should be either bolded, italicized or underlined. The script would then format the text sent over accordingly, and then pipe it back to C where the program would spit the output out into a text document.

The next part of this project was moving the entire process over to a website that I designed using a combination of HTML, CSS, javascript and PHP. The entire formatting process remained the same, we just moved it to run through a website GUI implementation that was hosted on a server instead of running it directly from command line. (If you decide to look at a4.php [file that contains html/css for website] the colours and fonts are very ugly because they allowed us to design it however we wanted with no mark deductions so I decided to have fun with it). The webpage allowed the user to select a text file of their choice through their computer’s file finder to upload to the server. From there the user could select the text file and convert it to a newly formatted HTML page (still utilizing the python and c code from previous iterations of the project). The resulting HTML page output was then available for the user to view through the webpage. The webpage displayed a list of available files on the server to be formatted, as well as a list of already formatted HTML files on the server that the user could view through the site.

The final part of the project was the simplest of all three previous iterations. I refactored the storage of the html files, moving them from a server directory to an SQL database. I wrote a few commands that allowed for creation, destruction and viewing of all available files inside of the database. The only changes on this portion of the project was moving storage of HTML files to an actual database.

caution
————————

If there is an extra line at end of the textfile that we read in from c, program hangs (remove that line if this is the case)


SOURCES
---------
- POPUP window using Javascript & CSS : youtube.com/watch?v=VnHvVz_bFKo
- UPLOAD ASSISTANCE : w3schools.com/php/php_file_upload.asp
- General help: w3schools.com/html

COMPILATION
------------------
make -> creates library, links & compiles with main program and creates executable called "a4"

make clean -> gets rid of executable file, library (architecture file), object files, & html files
