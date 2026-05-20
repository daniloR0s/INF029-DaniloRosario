char q8(char tab[3][3]){
    for(int i = 0; i < 3; i++){
        if(tab[i][0] == 'X' &&
           tab[i][1] == 'X' &&
           tab[i][2] == 'X'){
            return 'X';
        }
        if(tab[i][0] == 'O' &&
           tab[i][1] == 'O' &&
           tab[i][2] == 'O'){
            return 'O';
        }
    }
    for(int j = 0; j < 3; j++){
        if(tab[0][j] == 'X' &&
           tab[1][j] == 'X' &&
           tab[2][j] == 'X'){
            return 'X';
        }
        if(tab[0][j] == 'O' &&
           tab[1][j] == 'O' &&
           tab[2][j] == 'O'){
            return 'O';
        }
    }
    if(tab[0][0] == 'X' &&
       tab[1][1] == 'X' &&
       tab[2][2] == 'X'){
        return 'X';
    }
    if(tab[0][0] == 'O' &&
       tab[1][1] == 'O' &&
       tab[2][2] == 'O'){
        return 'O';
    }
    if(tab[0][2] == 'X' &&
       tab[1][1] == 'X' &&
       tab[2][0] == 'X'){
        return 'X';
    }
    if(tab[0][2] == 'O' &&
       tab[1][1] == 'O' &&
       tab[2][0] == 'O'){
        return 'O';
    }
    return 'E';
}


int main(){

   return 0;
}
