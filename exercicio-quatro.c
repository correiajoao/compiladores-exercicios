/* Universidade Federal de Alagoas - Campus A.C. Simões 
*  Aluno: João Correia
*  Codificar o analisador descendente preditivo recursivo da gramática abaixo
*/

Sendo a gramática abaixo:

(1) Calc = Ea '=' {printf("%f", Ea.val);}
(2) Ea = Ta {Ear.vh = Ta.val } Ear {Ea.val = Ear.vs} 
(3) Ear = '+' Ta {Ear1.vh = Ear.vh + Ta.val} Ear {Ear.vs=Ear1.vs}
(4) Ear = '-' Ta {Ear1.vh = Ear.vh - Ta.val} Ear {Ear.vs=Ear1.vs} 
(5) Ear = $ {Ear.vs = Ear.vh}
(6) Ta = Fa {Tar.vh = Fa.val} Tar {Ta.val = Tar.vs} 
(7) Tar = '*' Fa {Tar1.vh = Tar.vh * Fa.val} Tar {Tar.vs=Tar1.vs} 
(8) Tar = '/' Fa {Tar1.vh = Tar.vh / Fa.val} Tar {Tar.vs=Tar1.vs}
(9) Tar = $	{Tar.vs=Tar.vh}
(10) Fa = '(' Ea ')' {Fa.val = Ea.val}
(11) Fa = 'cteN' {Fa.val = atof(cteN.lex);}

Construção do analisador preditivo recursivo:

void Calc(){
	if(token.categ == ATR){
		token.next();
		printf("%f", Ea());	
	}
}

float Ea(){
	float Taval, Earvh, Earvs, Eaval;
	
	Taval=Ta();
	Earvh=Taval;
	Earvs=Ear(Earvh);
	Eaval= Earvs;
	return(Eaval);
}

float Ear(float Earvh){
	float Taval, Ear1vh, Ear1vs, Earvs;
	if(token.categ == MAIS){
		token.next();

		Taval = Ta();
		Ear1vh = Earvh + Taval; 
		Ear1vs = Ear(Ear1vh);
		Earvs = Ear1vs;
	}else if(token.categ == MENOS){
		token.next();

		Taval = Ta();
		Ear1vh = Earvh - Taval;
		Ear1vs = Ear(Ear1vh);
		Earvs = Ear1vs;
	}else{
		Earvs=Earvh;
	}
	return Earvs;
}

float Ta(){
	float Faval, Tarvh, Tarvs, Taval;
	Faval = Fa();
	Tarvh = Faval;
	Tarvs = Tar(Tarvh);
	Taval = Tarvs;
	return Taval;
}

float Tar(float Tarvh){
	float Faval, Tar1vh, Tar1vs, Tarvs;  
	if(token.categ == MULT){
		token.next();
		
		Faval = Fa();
		Tar1vh = Tarvh * Faval;
		Tar1vs = Tar(Tar1vh);
		Tarvs = Tar1vs;
	}else if(token.categ == DIV){
		token.next();

		Faval = Fa();
		Tar1vh = Tarvh / Faval;
		Tar1vs = Tar(Tar1vh);
		Tarvs = Tar1vs;
	}else{
		Tarvs = Tarvh;
	}
	return Tarvs;
}

float Fa(){
	float Faval, Eaval;
	if(token.categ == ABR_PAR){
		token.next();

		Eaval = Ea();
		Faval = Eaval;
		if(token.categ == FEC_PAR){
			token.next();
			return Faval;
		}else{
			printf("Erro: ')' esperado");
		}
	}else if(token.categ == CTEN) {
		token.next();
		Faval = atof(token.lex);
	}else{
		printf("Erro: '(' ou 'Constante' esperados");
	}
}
