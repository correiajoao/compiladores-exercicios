/* Universidade Federal de Alagoas - Campus A.C. Simões 
* Aluno: João Correia
* Pseudo código das funções de um analisador descendente preditivo recursivo. 
*/

int main(){
	//Abre o arquivo 
	//Cria o analisador léxico
	//Cria o token
	//Acessa o primeiro token	
    
    fpgm();
}

// pgm = ldecl '::' lsent'.'
void fpgm(){
	fldecl();
	if(tk.categ() == DPTDPT){
		tk.next();
		flsent(); //Implementar
		if(tk.categ() == PT){
			tk.next();
			if(tk.categ() == EOF){
				return;
			}else{
				erro(EOF, " esperado", tk)
			}
		}else{
			erro(PT, " esperado", tk);
		}
	}else{
		erro(DPTDPT, " esperado", tk);
	}
}

//ldecl = decl ldeclr
void fldecl(){
	fdecl();
	fldeclr();
}

// ldecl = ';' decl ldeclr | vazio
void ldeclr(){
	if(tk.categ() == PTV){
		tk.next();
		fdecl();
		fldeclr();
	}
}

//decl = lid ':' tipo
void fdecl(){
	flid();
	if(tk.next() == DPT){
		tk.next();
		ftipo();
	}else{
		erro(DPT, " esperado", tk);
	}
}

//lid = 'id' lidr
void flid(){
	if(tk.categ() == ID){
		tk.next();
		flidr();
	}else{
		erro(ID, " esperado", tk);
	}
}

//lidr = ',' 'id' lidr | vazio
void flidr(){
	if(tk.categ() == VG){
		tk.next();
		if(tk.categ() == ID){
			tk.next();
			flidr();
		}else{
			erro(ID, " esperado", tk);
		}
	}
}

//tipo = tbase tipof
void ftipo(){
	ftbase();
	ftipof();
}

//tipof = '[' ctei ']' | vazio  
void ftipof(){
	if(tk.categ() == AC){
		tk.next();
		fctei();
		if(tk.next() == FC){
			tk.next();
		}else{
			erro(FC, " esperado", tk);
		}
	}
}

//tbase = 'int' | 'real'
void ftbase(){
	if(tk.categ() == INT){
		tk.next();
	}else if( tk.categ() == REAL){
		tk.next();
	}else{
		erro(INT, "ou", REAL, " esperado", tk);	
	}
}

//lsent = sent lsentr
void flsent(){
	fsent();
	flsentr();
}


//lsentr = ';'sent lsentr
void flsentr(){
	if(tk.categ() == PTV){
		tk.next();
		fsent();
		flsentr();
	}
}

//sent = atr | cond | iter
void fsent(){
	if(tk.categ() == ID){
		fatr();	
	}else if(tk.categ() == SE){
		fcond();
	}else if(tk.categ() == PARA || tk.categ() == ENQUANTO || tk.categ() == REPITA){
		finter();
	}
}

//atr = 'id' '=' ea
void fatr(){
	if(tk.categ() == ID){
		tk.next();
		 if(tk.categ() == IG){
		 	tk.next();
		 	fea();
		 }else{
		 	erro(IG, " esperado", tk);
		 }
	}else{
		erro(ID, " esperado", tk);
	}
}

//cond = 'se' eb 'entao' lsent condf
void fcond(){
	if(tk.categ() == SE){
		tk.next();
		feb();
		if(tk.categ() == ENTAO){
			tk.next();
			flsent();
			fcondf();
		}else{
			erro(ENTAO, "esperado", tk);
		}
	}else{
		erro(SE, " esperado", tk)
	}
}

//condf = 'senao' lsent 'fim' | fim
void fcondf(){
	if(tk.categ() == SENAO){
		tk.next();
		flsetn();
		if(tk.categ() == FIM){
			tk.next();
		}else{
			erro(FIM, " esperado", tk);
		}
	}else if (tk.categ() == FIM){
		tk.next();
	}else{
		erro(SENAO, "ou", FIM, " esperado", tk);
	}

//iter = 'para' atr 'ate'  ea passo 'faca' lsent 'fim' | 'enquanto' eb 'faca' lsent 'fim' | 'repita' lsent 'enquanto' eb 'fim'
void fiter(){
	if(tk.categ() == PARA){
		tk.next();
		fatr();
		if(tk.categ() == ATE){
			tk.next();
			fea();
			fpasso();
			if(tk.categ() == FACA){
				tk.next();
				flsent();
				if(tk.categ() == FIM){
					tk.next();
				}else{
					erro(FIM, " esperado", tk);
				}
			}else{
				erro(FACA, " esperado", tk);
			}
		}else{
			erro(ATE, " esperado");
		}	
	}else if(tk.categ() == ENQUANTO){
		tk.next();
		feb();
		if(tk.categ() == FACA){
			tk.next();
			flsent();
			if(tk.categ() == FIM){
				tk.next();
			}else{
				erro(FIM, " esperado", tk);
			}
		}else{
			erro(FACA, " esperado", tk);
		}
	}else if(tk.categ() == REPITA){
		tk.next();
		flsent();
		if(tk.categ() == ENQUANTO){
			tk.next();
			feb();
			if(tk.categ() == FIM){
				tk.next();
			}else{
				erro(FIM, " esperado", tk);
			}
		}else{
			erro(ENQUANTO, " esperado", tk);
		}
	}else{
		erro(PARA, ",",ENQUANTO, "ou", REPITA " esperado", tk);
	}
} 

//passo = 'passo' ea | vazio
void fpasso(){
	if(tk.categ() == "passo"){
		tk.next();
		fea();
	}
}