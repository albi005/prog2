#!/usr/bin/env python3
import faker
import random
from datetime import datetime, timedelta

fake = faker.Faker('hu_HU', use_weighting=True)
faker.Faker.seed(0)

# https://www.fressnapf.hu/kutyanev-hatarozo/
animal_names = ["Adolf", "Adolfa", "Afton", "Albert", "Alcsi", "Alfi", "Alfonz", "Alfy", "Alma", "Álmi", "Álmos", "Apszi", "Archie", "Argon", "Arnold", "Árnyék", "Artemon", "Aslan", "Balta", "Balu", "Barney", "Báró", "Beau", "Becks", "Béla", "Beni", "Benjamin", "Benny", "Bentley", "Bernárd", "Bernat", "Betti", "Bloff", "Boborján", "Body", "Bogáncs", "Bonca", "Bora", "Brandy", "Bright", "Brunó", "Buddy", "Cefre", "Cornelius", "Csipu", "Cyndi", "Dáma", "Darcy", "Dasha", "Dezső", "Dínó", "Dió", "Dodi", "Dönci", "Dörmi", "Duncan", "Eddy", "Elmo", "Fecsó", "Frida", "Fruzsina", "Fülöp", "Gandalf", "Gandhi", "Gerbeaud", "Gibert", "Gina", "Gnar", "Gréta", "Gvendolyn", "Hektor", "Hetty", "Hotch", "Huba", "Hugó", "Iván", "Jenna", "Jimmy", "Jo", "Jockey", "Johnnie", "Kommancs", "Kormi", "Lajos", "Lali", "Larry", "Lator", "Lazy", "Lecsó", "Léda", "Lekvár", "Léna", "Limó", "Lord", "Ludó", "Luise", "Lujza", "Luna", "Lupo", "Macesz", "Maci", "Macika", "Mafla", "Mágus", "Majcsi", "Májki", "Makacs", "Malou", "Mámor", "Mamuk", "Mamusz", "Mandu", "Mao", "Mardel", "Marley", "Maxi", "Medve", "Melody", "Menfisz", "Merlin", "Misa", "Misi", "Molli", "Montel", "Moon", "Morcos", "Morfeus", "Moritz", "Nella", "Neo", "Nephelé", "Nimród", "Norbi", "Odry", "Olaf", "Oleg", "Oma", "Oppa", "Óriás", "Oscar", "Oskar", "Panda", "Panni", "Passz", "Philip", "Porcika", "Pupi", "Ramses", "Ramszesz", "Rebarbara", "Regin", "Retro", "Rhodesian", "Rozmaring", "Rozsdás", "Sába", "Sädy", "Said", "Sam", "Sámson", "Samu", "Sámuel", "Samy", "Sanyi", "Sanyibá", "Sharon", "Shirley", "Shrek", "Soma", "Stanley", "Szundi", "Szuszi", "Szuszika", "Szuszu", "Teodor", "Theodor", "Toldo", "Toto", "Trevor", "Vendel", "Vincent", "Zsombor", "Zsuzsanna", "Zsuzsi", "Zsuzska"]

o = open("owners", mode="w")
a = open("animals", mode="w")
t = open("treatments", mode="w")

current_date = datetime.now()
ten_years_ago = current_date - timedelta(days=365*10)

animalId = 0
treatmentId = 0
for ownerId in range(1,30):
    print(ownerId, file=o)
    print(fake.last_name(), fake.first_name(), file=o)
    print(fake.street_address(), file=o)
    print(random.choice([
        "+36" + str(random.randint(100000000, 999999999)),
        fake.free_email()
    ]), file=o)

    for _ in range(random.randint(0,5)):
        animalId += 1
        print(animalId, file=a)
        print(ownerId, file=a)
        print(random.choice(animal_names), file=a)
        print(random.choice(["Kutya", "Macska", "Kutya", "Macska", "Kutya", "Macska", "Nyúl", "Hörcsög", "Egér"]), file=a)

        treatmentDates = sorted([fake.unix_time(start_datetime=ten_years_ago, end_datetime=current_date) for _ in range(random.randint(0,10))])
        for date in treatmentDates:
            treatmentId += 1
            print(treatmentId, file=t)
            print(animalId, file=t)
            print(int(date), file=t)
            print(random.randint(0,1), file=t)
            print("Kezelés leírása ide", file=t)
