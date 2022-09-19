# QtPCPartPicker
 PC Part Picker Qt6 Application


##### Objective:
I wanted to research a bit on C++ after taking a course (Systems Progamming) in uni which delved very little into it, and decided to learn Qt6.

##### Idea:
Similarly to the website https://pcpartpicker.com/ (which helps ensure compatibility) I wanted to create a database which could generate compatible computer spec sheets based on a given price point and use-case (e.g office work, gaming, servers etc)

I decided that I would rather work on my OOP and design skills and focus on C++ and learning Qt6 and how to utilize Qt Objects, therefore I decided to solely program in C++ and Qt6, rather than to use SQL queries.

##### Implementation:
Using OOP, I made inheritence trees for each PC part. 
I created a local database (based on importing and exporting JSON files) to store all the relevant data for the *'existing stock'*.
Lastly, compatibility checks are done using the QtObject signals and slots, to ensure that the returned spec sheet is fully compatible. 
