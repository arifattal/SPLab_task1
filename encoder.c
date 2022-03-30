#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void oneA();
void oneB();
void oneC();
void oneD();
void two();

int main(int argc, char **argv){
    //oneA();
    //oneB(argc, argv);
    //oneC(argc, argv);
    //oneD(argc, argv);
    two(argc, argv);
    return 0;
}

void oneA(){
    FILE* out = stdout;
    FILE* in =  stdin;
    char data;
    while((data = fgetc(in)) != '\n'){
        if(data>=65 && data<=90){
            printf("%c", '.');
        }
        else{
            printf("%c", data);
        }
    }
    printf("%c", '\n'); //drop line
    fclose(out);
}

void oneB(int argc, char **argv){
    FILE* out = stdout;
    FILE* in =  stdin;
    int DebugMode = 0;
    if(argc==3 && strcmp(argv[2], "-D") == 0){//checks if we are in debug mode, strcmp compares two strings, and return 0 if true
        DebugMode = 1;}
    char data;
    int numOfCaps = 0; //stores number of capital letters in string
    while((data = fgetc(in)) != '\n'){
        if(data>=65 && data<=90){ //check if cap letter
            if(DebugMode == 1){ //do bollocks with numbers
                numOfCaps++;
                fprintf( stderr, "%d", data);
                fprintf( stderr, "%c", ' ');
                fprintf( stderr, "%d", '.');
                fprintf( stderr, "%c", '\n');
            }
            printf("%c", '.'); //replace cap with . if in debug or not
        }
        else{ //if not cap letter
            printf("%c", data);
            if(DebugMode == 1) { //do bollocks with numbers
                fprintf(stderr, "%d", data);
                fprintf(stderr, "%c", ' ');
                fprintf(stderr, "%d", data);
                fprintf(stderr, "%c", '\n');
            }
        }
    }
    if(DebugMode == 1) { //print number of letter line
        fprintf(stderr, "%c", '\n');
        fprintf(stderr, "%s", "the number of letters: ");
        fprintf(stderr, "%d", numOfCaps);
        fprintf(stderr, "%c", '\n');
    }
    printf("%c", '\n'); //end with \n
    fclose(out);
}

void oneC(int argc, char **argv){
    FILE* out = stdout;
    FILE* in = stdin;
    char data;
    int mode = 0; //plus or minus
    int num = 0;
    int encMode = 0;
    char first;
    int firstSaved = 0; //a flag that lets us save the first char

    for(int i =0; i<argc; i++){ //flag the mode chosen
        if((argv[i][0] == '-' || argv[i][0] == '+') && argv[i][1] == 'e'){ //enc mode
            encMode = 1;
            if(argv[i][0] == '+'){
                mode = 1;
            }
            if ((int) argv[i][2] > 47 && (int) argv[i][2] < 58) {
                num = (int) argv[i][2] - 48; //0-9
            }
            else {
                num = (int) argv[i][2] - 55; //A-F
            }
        }
    }
        if((mode == 1) && (encMode == 1)){ //plus sign and encode mode
            while((data = fgetc(in)) != '\n'){
                if(firstSaved == 0){//save the first char
                    first = data;
                    firstSaved = 1;
                }
                printf("%c", data);
            }
            while(num != 0){ //print the first char an extra num times
                printf("%c", first);
                num = num - 1;
            }
            printf("%c", '\n'); //drop line
        }
        else if((mode == 0) && (encMode == 1)){
            while((data = fgetc(in)) != '\n'){
                if(num > 0){ //ignore first num characters
                    num = num -1;
                }
                else{
                    printf("%c", data);
                }
            }
            printf("%c", '\n'); //drop line
        }
        else{
            oneA();
        }
    fclose(out);
    }


void oneD(int argc, char **argv){
    char data;
    int t = 1;
    int mode = 0; //plus or minus
    int num = 0;
    int encMode = 0;
    int inMode = 0;
    char first;
    int firstSaved = 0; //a flag that lets us save the first char
    for(int i =0; i<argc; i++){ //flag the mode chosen
        if((argv[i][0] == '-' || argv[i][0] == '+') && argv[i][1] == 'e'){ //enc mode
            encMode = 1;
            if(argv[i][0] == '+'){
                mode = 1;
            }
            if ((int) argv[i][2] > 47 && (int) argv[i][2] < 58) {
                num = (int) argv[i][2] - 48; //0-9
            } else { // A-F
                num = (int) argv[i][2] - 55;
            }
        }
        else if(argv[i][0] == '-' && argv[i][1] == 'i'){ //input mode
            inMode = 1;
        }
    }

    if(inMode == 1){//file input mode
        FILE *fp;
        for(int i =0; i<argc; i++){
            if(argv[i][0] == '-' && argv[i][1] == 'i'){ //input mode
                fp = fopen(argv[i] + 2, "r");
                if (!fp){
                    printf("%s", "file does not exist");
                    exit(EXIT_FAILURE);
                }
            }
        }
        if( fp != NULL){
            if(encMode == 1 && mode == 1){ //encryption mode and plus sign
                while(t == 1) {
                    data = fgetc(fp); //get letter from file
                    if(data == EOF){ //break while loop
                        t = 0;
                    }
                    if(firstSaved == 0){//save the first char
                        first = data;
                        firstSaved = 1;
                    }
                    if(t == 1){
                        printf("%c", data);} //print letter from file
                }
                while(num != 0){ //print the first char an extra num times
                    printf("%c", first);
                    num = num - 1;
                }
                printf("%c", '\n'); //drop line
            }
            else if(encMode == 1 && mode == 0){//encryption mode and minus sign
                while(t == 1) {
                    data = fgetc(fp); //get letter from file
                    if(data == EOF){ //break while loop
                        t = 0;
                    }
                    if(num > 0){
                        num = num -1;
                    }
                    else if(t == 1){
                        printf("%c", data);} //print letter from file
                }
                printf("%c", '\n'); //drop line
            }
            else if(encMode == 0){ //only input mode
                while(t == 1) {
                    data = fgetc(fp); //get letter from file
                    if(data == EOF){ //break while loop
                        t = 0;
                    }
                    if(t == 1){
                        if(data>=65 && data<=90){
                            printf("%c", '.');
                        }
                        else{
                            printf("%c", data);
                        }
                    } //print letter from file
                }
                printf("%c", '\n'); //drop line
            }
        }
        fclose(fp);
    }
    else if(inMode == 0 && encMode == 1){ //encryption mode only
        oneC(argc, argv);
    }
    else{ //no encryption and no file reading
        oneA();
    }

}

void two(int argc, char **argv){
    char data;
    int t = 1;
    int mode = 0; //plus or minus
    int num = 0;
    int outMode = 0;
    int inMode = 0;
    int encMode = 0;
    char first;
    int firstSaved = 0; //a flag that lets us save the first char
    for(int i =0; i<argc; i++){ //flag the mode chosen
        if((argv[i][0] == '-' || argv[i][0] == '+') && argv[i][1] == 'e'){ //enc mode
            encMode = 1;
            if(argv[i][0] == '+'){
                mode = 1;
            }
            if ((int) argv[i][2] > 47 && (int) argv[i][2] < 58) {
                num = (int) argv[i][2] - 48; //0-9
            } else { // A-F
                num = (int) argv[i][2] - 55;
            }
        }
        else if(argv[i][0] == '-' && argv[i][1] == 'o'){ //output mode
            outMode = 1;
        }
        else if(argv[i][0] == '-' && argv[i][1] == 'i'){ //input mode
            inMode = 1;
        }
    }
    if(outMode == 0){ //this is identical to oneD
        printf("%c", 't');
        oneD(argc, argv);
    }
    else if(outMode == 1 && inMode == 1 && encMode == 1){ //all modes are applied
        FILE *fr; //file read
        FILE *fw; //file write
        for(int i =0; i<argc; i++){
            if(argv[i][0] == '-' && argv[i][1] == 'o'){ //output mode
                fw = fopen(argv[i] + 2, "w");
            }
            else if(argv[i][0] == '-' && argv[i][1] == 'i'){ //input mode
                fr = fopen(argv[i] + 2, "r");
                if (!fr){ //throw exception if file does not exist
                    printf("%s", "file does not exist");
                    exit(EXIT_FAILURE);
                }
            }
        }
        if(fr != NULL){
            if(mode == 1){ //plus sign
                while(t == 1) {
                    data = fgetc(fr); //get character from file
                    if(data == EOF){ //break while loop
                        t = 0;
                    }
                    if(firstSaved == 0){//save the first char
                        first = data;
                        firstSaved = 1;
                    }
                    if(t == 1){
                        fputc(data, fw);} //print letter from file
                }
                while(num != 0){ //print the first char an extra num times
                    fputc(first, fw);
                    num = num - 1;
                }
            }
            else if(mode == 0){//encryption mode and minus sign | only read file mode(covers this case)
                while(t == 1) {
                    data = fgetc(fr); //get letter from file
                    if(data == EOF){ //break while loop
                        t = 0;
                    }
                    if(num > 0){
                        num = num - 1;
                    }
                    else if(t == 1){
                        fputc(data, fw);} //print letter from file
                }
            }
        }
        fclose(fr);
        fclose(fw);
    }
    else if(outMode == 1 && inMode == 0 && encMode == 1){ //output mode and encryption
        FILE *fw; //file write
        FILE* out = stdout;
        FILE* in = stdin;
        for(int i =0; i<argc; i++){
            if(argv[i][0] == '-' && argv[i][1] == 'o'){ //output mode
                fw = fopen(argv[i] + 2, "w");
            }
        }
        if(mode == 1){ //plus sign
            while((data = fgetc(in)) != '\n'){
                if(firstSaved == 0){//save the first char
                    first = data;
                    firstSaved = 1;
                }
                fputc(data, fw);
            }
            while(num != 0){ //print the first char an extra num times
                fputc(data, fw);
                num = num - 1;
            }
        }
        if(mode == 0){
            while((data = fgetc(in)) != '\n'){
                if(num > 0){ //ignore first num characters
                    num = num - 1;
                }
                else{
                    fputc(data, fw);
                }
            }
        }
        fclose(fw);
        fclose(out);
    }
    else if(outMode == 1 && inMode == 0 && encMode == 0){
        FILE *fw; //file write
        FILE* out = stdout;
        FILE* in = stdin;
        for(int i =0; i<argc; i++){
            if(argv[i][0] == '-' && argv[i][1] == 'o'){ //output mode
                fw = fopen(argv[i] + 2, "w");
            }
        }
        while((data = fgetc(in)) != '\n') {
            if(data>=65 && data<=90){
                fputc('.', fw);
            }
            else{
                fputc(data, fw);
            }
        }
        fclose(fw);
        fclose(out);
        }
    else if(outMode == 1 && inMode == 1 && encMode == 0){//output mode and input mode
        FILE *fr; //file read
        FILE *fw; //file write
        for(int i =0; i<argc; i++){
            if(argv[i][0] == '-' && argv[i][1] == 'o'){ //output mode
                fw = fopen(argv[i] + 2, "w");
            }
            else if(argv[i][0] == '-' && argv[i][1] == 'i'){ //input mode
                fr = fopen(argv[i] + 2, "r");
                if (!fr){ //throw exception if file does not exist
                    printf("%s", "file does not exist");
                    exit(EXIT_FAILURE);
                }
            }
        }
        if(fr != NULL){
            while(t == 1){
                data = fgetc(fr);
                if(data == EOF){
                    t = 0;
                }
                if(t == 1){
                    if(data>=65 && data<=90){
                        fputc('.', fw);
                    }
                    else{
                        fputc(data, fw);
                        }
                    }
            }
            fclose(fw);
        }
    }
}