import csv
from datetime import datetime, timedelta


def main():
    recycling_dates = []
    with open('bin_recycling.csv', 'r') as file:
        csv_reader = csv.reader(file)
        for row in csv_reader:
            recycling_dates.append(datetime.strptime(str(row[0]), "%d/%m/%Y"))
    # Add 9 hours to every date
    for index in range(len(recycling_dates)):
        recycling_dates[index] = recycling_dates[index] + timedelta(hours=9)    
    # Assert that all the dates are in order
    for index in range(1, len(recycling_dates)):
        if recycling_dates[index] < recycling_dates[index - 1]:
            print("Recycling dates are not chronological")
            return
    
    landfill_dates = []
    with open('bin_landfill.csv', 'r') as file:
        csv_reader = csv.reader(file)
        for row in csv_reader:
            landfill_dates.append(datetime.strptime(str(row[0]), "%d/%m/%Y"))
    # Add 9 hours to every date
    for index in range(len(landfill_dates)):
        landfill_dates[index] = landfill_dates[index] + timedelta(hours=9)    
    # Assert that all the dates are in order
    for index in range(1, len(landfill_dates)):
        if landfill_dates[index] < landfill_dates[index - 1]:
            print("Landfill dates are not chronological")
            return

    print("LANDFILL_ENTRIES: \"" + str(int(len(landfill_dates))) + "\"")
    print("LANDFILL_UNIX: \"" + str(int(landfill_dates[0].timestamp())))
    for i in landfill_dates[1:]:
        print("  " + str(int(i.timestamp())))
    print("  \"")
    print("RECYCLING_ENTRIES: \"" + str(int(len(recycling_dates))) + "\"")
    print("RECYCLING_UNIX: \"" + str(int(recycling_dates[0].timestamp())))
    for i in recycling_dates[1:]:
        print("  " + str(int(i.timestamp())))
    print("  \"")


if __name__ == '__main__':
    main()