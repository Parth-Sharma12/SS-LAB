            int extractNumericId(const char *id) {
                int numericId;
                sscanf(id, "iiitb@%d", &numericId);
                return numericId;
            }
            void generateNewId(char *newId, int highestId) {
                sprintf(newId, "iiitb@%d", highestId + 1);
            }
            
            char id[50];
            char name[50];
            char department[50];
            char email[50];
            char address[100];
            char designation[50];

            int highestNumericId = 0;

            // Open the file for reading to find the highest existing numeric ID

            // Read the existing data and find the highest numeric ID
            while (fscanf(file1, "Id: %s\n", id) == 1) {
                int numericId = extractNumericId(id);
                if (numericId > highestNumericId) {
                    highestNumericId = numericId;
                }

                // Read and discard the other information
                fscanf(file1, "Name: %s\n", name);
                fscanf(file1, "Email: %s\n", email);
                fscanf(file1, "Address: %s\n", address);
            }
            //printf("HighestId:%d",highestNumericId);

            char ID_[20];
            generateNewId(ID_,highestNumericId);
            printf("%s",ID_);
            // Write the received data to the text file
            fprintf(file1, "ID: %s\n", ID_);
            fprintf(file1, "Password: %s\n", student.password);
            fprintf(file1, "Name: %s\n", student.name);
            fprintf(file1, "Email: %s\n",student.email);
            fprintf(file1, "Address: %s\n", student.address);
           ;