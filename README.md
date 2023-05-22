# ShadowByte Botnet
Complete Botnet Infrastucture with Malicious C&amp;C Server And Malware Agents to infect Windows OS

A completely botnet infrastructure created with C++ in victim side and Web Languages (HTML,CSS,JavaScript and PHP) in malicious server in attacker side.

The architecture of Shadow Byte is truly remarkable, combining the robustness of C++ for the victim-side code with the flexibility and interactivity of web languages such as HTML, CSS, JavaScript, and PHP on the attacker's server. This lethal combination allows for seamless communication between the infected machines and the centralized command and control server.

# Server C&C 
**Pages**

The C&C server only have 2 pages, the Login page and the home page with the list of all the zombies.

Home Page:

![image](https://github.com/S12cybersecurity/ShadowByte-Botnet/assets/79543461/0ec89af1-1106-4d79-947a-5c0aa7f77917)

This is the home page, this page have various features, first of all show the SQLite database entries, this represents all the zombies in the botnet.
Other feature of the home page it's the possibility to execute a command in all the zombies inserted in the database.

The last feature of the page its the possibility to logout from your actually user.

Login Page

![image](https://github.com/S12cybersecurity/ShadowByte-Botnet/assets/79543461/7eafd952-f61e-48c8-974c-423e86f8e6b7)

This login its very simple, like the name, its a login connected with the SQLite Database.

And now we see in action the agent malware code, this part of botnet infrastructure represents the binary executed in victim system.

Basically the malware code its composted by 2 binary files, one in the victim system and the other hosted into the malicious C&C Server.

The binary stored and executed as administrator in victim machine send a http petition to add this machine in the zombies server list, then download the other binary file, this downloaded binary file it's a Windows Services executable, and the next step of binary executed in victim machine it's create a persistent service with the binary downloaded and then the first binary he finish her function and you can delete it.

Once this moment you don't need to do or execute anything more in victim machine, now you have completely remote code execution into victim machine.

Let's show you the use with screenshots:

First i start my apache service to host the C&C Server.

![image](https://github.com/S12cybersecurity/ShadowByte-Botnet/assets/79543461/65de4d0d-4196-4631-8386-4388f8169b8b)

I log in:

![image](https://github.com/S12cybersecurity/ShadowByte-Botnet/assets/79543461/58d200b9-71af-4e1e-9edc-1a398eb2edfa)

![image](https://github.com/S12cybersecurity/ShadowByte-Botnet/assets/79543461/b1badc8c-15f6-4d13-ae82-ad302da4e777)

Let's execute the malware binary:

![image](https://github.com/S12cybersecurity/ShadowByte-Botnet/assets/79543461/9c37f0d5-19ed-4423-ad22-0f4b9da9c808)

![image](https://github.com/S12cybersecurity/ShadowByte-Botnet/assets/79543461/17297821-13e3-4e0a-a1cd-b175d7ef23f6)

Run as administrator, and now i check if i have the service called zombie created:

![image](https://github.com/S12cybersecurity/ShadowByte-Botnet/assets/79543461/31e184b5-a983-441e-82df-22a950987dd3)

And when i restart the Windows OS, the service are started:

![image](https://github.com/S12cybersecurity/ShadowByte-Botnet/assets/79543461/6b4f88a2-e85c-48a2-9a18-c733f6bb88d2)

Now in the Server C&C i can execute a command:

![image](https://github.com/S12cybersecurity/ShadowByte-Botnet/assets/79543461/05513823-0c62-4bbc-9663-c60ac22e711b)

And i click send:

![image](https://github.com/S12cybersecurity/ShadowByte-Botnet/assets/79543461/29120b7c-eb32-4695-8524-b56503ebc446)

The file its created and this is his content:

![image](https://github.com/S12cybersecurity/ShadowByte-Botnet/assets/79543461/a03e0692-5f03-4d5a-b9e3-f00d7c163adf)
