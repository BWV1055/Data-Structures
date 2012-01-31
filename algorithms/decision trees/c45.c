/*
 *	C4.5 algorithm, the successor of ID3, for building decision trees
 */

#include <math.h>

struct dec_node {
	/* Outlook */
	int att_n;
	/* Each attribute has values: Sunny, Overcast, Rain */
	int sample_n;
	int* sample_v;
	/* Sunny: 5, Overcast: 4, Rain: 5 */
	int* sample_f;
	int chd_n;
	struct dec_node** chd;
};

struct dec_tree {
	struct dec_node* root;
	/* 4 or less if data is classified perfectly earlier */
	int attribs_n;
	/* Used Outlook, Humidity and Wind */
	int* attribs;
	int classif_n;
	/* YES/NO */
	int* classif;
};

float entropy_c(int* a[], int attrib, int attrib_v, int n_entries, int cc) {
	int i, classif, total = 0, a_v_c;
	int* c_f = calloc(n_entries*sizeof(int));
	float e = 0;
	for(i=0;i<n_entries;i++)
		/* Weak wind */
		if(a[i][attrib] == attrib_v) {
			classif = a[i][cc];
			c_f[classif]++;
			total++;
		}
	for(i=0;i<n_entries;i++)
		if(a_v_c = c_f[i])
			e-=(a_v_c/total)*log2(a_v_c/total);
	free(c_f);
	return e;
}

float entropy(int* a[], int n_entries, int cc) {
	float e = 0;
	int i;
	int* values = calloc(n_entries*sizeof(int));
	for(i=0;i<n_entries;i++) 
		values[a[i][cc]]++;
	for(i=0;i<n_entries;i++)
		if(values[i])
			e-=values[i]/n_entries*log2(values[i]/n_entries);
	return e;
}
/* Values appear in increasing order on a column 
 * Sunny<Overcast<Rain because this is the order in which they appear in the column */
float gain(int* a[], int attrib, int n_entries, int cc) {
	float g = 0;
	int i;
	int* attrib_values = calloc(n_entries*sizeof(int));
	for(i=0;i<n_entries;i++)
		attrib_values[a[i][attrib]]++;
	for(i=0;i<n_entries;i++) 
		if(attrib_values[i])
			g-=attrib_values[i]/n_entries*entropy_c(a, attrib, attrib_values[i], n_entries, cc);
	g+=entropy(a, n_entries, cc);
	return g;
}

/* n_attrib includes the classification column, last */
struct dec_tree* c45(char* training_data[], int n_attrib) {
	char *c;
	int col = 0, line = 0, cur_total = 0;

	c = training_data[0];
	while(strcmp(c, NULL)) {
		cur_total++;
		if(cur_total%n_attrib==0){
			line++;
			col=0;
		}
		switch col {
			case 0: {
				if(strcmp(c, "SUNNY")==0) a[line][col] = 0;
				else if(strcmp(c, "OVERCAST")==0) a[line][col] = 1;
				else if(strcmp(c, "RAIN")==0) a[line][col] = 2;
				else return NULL;
			}
			case 1: {
				if(strcmp(c, "HOT")==0) a[line][col] = 0;
				else if(strcmp(c, "MILD")==0) a[line][col] = 1;
				else if(strcmp(c, "COLD")==0) a[line][col] = 2;
				else return NULL;
			}
			case 2: {
				if(strcmp(c, "HIGH")==0) a[i][j] = 0;
				else if(strcmp(c, "NORMAL")==0) a[i][j] = 1;
				else return NULL;
			}
			case 3: {
				if(strcmp(c, "WEAK")==0) a[i][j] = 0;
				else if(strcmp(c, "STRONG")==0) a[i][j] = 1;
				else return NULL;
			}
			case 4: {
				if(strcmp(c, "NO")==0) a[i][j] = 0;
				else if(strcmp(c, "YES")==0) a[i][j] = 1;
				else return NULL;
			}
			default:
				break;
		}
		c = training_data[cur_total];
	}

	struct dec_tree* d_tree = malloc(sizeof(*d_tree));

	while()

}

char* training_data[] = 
{
 /*	Outlook  Temperature   Humidity      Wind   Classification */  
 	"SUNNY",  	"HOT",    	"HIGH",    	"WEAK",		"NO",
	"SUNNY",	"HOT",    	"HIGH",    	"STRONG",	"NO",
	"OVERCAST",	"HOT",    	"HIGH",   	"WEAK",		"YES",
	"RAIN",		"MILD",   	"HIGH",   	"WEAK",		"YES",
	"RAIN",		"COOL",		"NORMAL",  	"WEAK",		"YES",
	"RAIN",		"COOL",  	"NORMAL",  	"STRONG",	"NO",
	"OVERCAST",	"COOL",  	"NORMAL",  	"STRONG",	"YES",
	"SUNNY", 	"MILD",  	"HIGH",    	"WEAK",		"NO",
	"SUNNY", 	"COOL",  	"NORMAL",  	"WEAK",		"YES",
	"RAIN",		"MILD",  	"NORMAL",  	"WEAK",		"YES",
	"SUNNY", 	"MILD",  	"NORMAL",  	"STRONG",	"YES",
	"OVERCAST",	"MILD",  	"HIGH",    	"STRONG",	"YES",
	"OVERCAST",	"HOT", 		"NORMAL",  	"WEAK",		"YES",
	"RAIN",  	"MILD",  	"HIGH",		"STRONG",	"NO",	
	NULL
};
