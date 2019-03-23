#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <iostream>
#include <cstdio>
#include <cmath>
#define int long long

using namespace std;
const int MOD = 1e9 + 7, maxn = 1e5 + 10, divide = 300000;

int bg[maxn], ne[maxn << 1], to[maxn << 1], e = 1;
inline void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}

template <typename T> T read()
{
	T ans = 0, p = 1;
	char c = getchar();
	while (!isdigit(c))
	{
		if (c == '-') p = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * p;
}

int n, m, L, R, ans;

int grand[maxn][20], LOG, depth[maxn];

void dfs(int x)
{
	for (int i = bg[x]; i ; i = ne[i])
		if (to[i] ^ grand[x][0])
		{
			depth[to[i]] = depth[grand[to[i]][0] = x] + 1;
			dfs(to[i]);
		}
}

int get_lca(int x, int y)
{
	if (depth[x] < depth[y]) swap(x, y);
	DREP(i, LOG, 0)
		if (depth[grand[x][i]] >= depth[y]) x = grand[x][i];
	if (x == y) return x;
	DREP(i, LOG, 0)
		if (grand[x][i] ^ grand[y][i]) x = grand[x][i], y = grand[y][i];
	return grand[x][0];
}

namespace violence
{
	int col[maxn];
	void calc()
	{
		int Min = n + 5;
		REP(i, 1, n)
			REP(j, i + 1, n)
			if (col[i] == col[j]) chkmin(Min, depth[i] + depth[j] - depth[get_lca(i, j)] * 2);
		ans += (L <= Min && Min <= R);
	}
	void color(int x)
	{
		if (x == n) calc();
		else
		{
			x++;
			REP(i, 1, m)
			{
				col[x] = i;
				color(x);
			}
		}
	}
	void work() {color(0);}
}
int de[maxn];
bool islian()
{
	REP(i, 1, n)
		if (de[i] > 2) return 0;
	return 1;
}

int power_pow(int a, int b)
{
	int ans = 1, base = a;
	while (b)
	{
		if (b & 1) ans = ans * base % MOD;
		base = base * base % MOD;
		b >>= 1;
	}
	return (ans + MOD) % MOD;
}
#define inv(x) power_pow(x, MOD - 2)

namespace cheat1
{
	int fac[] = {1,373281933,679209364,730342129,363599536,448516387,663484182,229611066,585806050,816761238,5832229,932799119,150478174,358784546,544918953,59433257,278955367,293296655,473966292,214054614,316220877,652382508,405577532,257438891,24521750,304661605,14422365,808427728,220087090,295620142,980250487,839684660,764421236,345911460,152611299,681184885,140864216,733842728,461157687,642502601,95936601,382610562,569582206,784835785,959173997,391177708,508362944,33592533,275742306,889166166,598816162,344176836,564190300,977909564,632048012,810640932,851161246,551739578,605016577,566161015,626497524,512332467,475501650,652967545,52298443,406755567,125625755,708750650,385457627,899820643,245341950,725000295,754437203,970854495,524308015,913230882,792180189,192185054,788944266,734897886,968999,642903797,511710008,3525929,979137619,328019447,30153596,610696318,353049206,500956856,881746146,87892573,919203761,122316469,910061172,560607302,542955556,31318378,496532173,778006566,76479948,126712923,941723214,85186984,685075984,30473806,581968000,348586163,451116854,448457825,886294336,570443478,695702195,107560517,229827108,771153434,296974594,546178363,204857297,656049509,544075857,876081033,632593345,642498983,854821744,468116664,466541843,644759890,198998756,836550874,82926604,848688381,924258126,960862718,535478979,320608814,63932312,571781438,305569485,710807771,721996174,979809664,526281212,44756165,522961673,814440466,589831644,21771073,268164416,364347439,172827403,106892865,169338716,455503344,675113999,983975503,475501867,852493922,415376,146628257,294587621,103228118,875018827,274155554,172340144,676243000,43217172,912590546,16783532,95325827,497478507,511176934,581794056,638088240,404666335,726686688,850677980,412956409,12568481,998406941,228338256,703470628,52378412,21373798,445935909,583676448,650765251,957424115,808076198,783200314,746536789,996955070,152366450,132350382,415355660,249780014,333236625,504223583,570866962,938204550,27368307,777338999,849148138,484723081,422227498,44635470,243833737,437862846,89372661,152019116,5974669,627402642,833342486,505819550,468608739,679975009,59143878,313702365,635032673,311539953,86609485,945754267,586359929,631326068,724008021,607649469,135711291,996881960,324648749,639334305,371263376,745897488,61732363,75142816,279914778,527225600,9409022,896155508,358050946,713802282,808412394,703420540,724209709,768955866,79329551,409420559,930161980,776363214,62785084,275062583,1669644,863596908,929666976,228137471,974936549,470618701,703087658,845285046,880634238,858493510,595143852,727281230,666743467,760927536,243910108,727223125,469594245,436778250,274161939,161004891,526807168,320466978,54080847,249481023,754963083,775147177,588618211,982508606,293401592,795558854,459188207,458068555,304228537,817509706,947251800,669251006,701643375,522396951,349343101,413937464,840398449,445438821,704289349,405638730,121102289,556957390,961729079,460879693,270409779,491891996,888050723,2840333,756462483,552487230,247544137,196710441,489872437,289842964,534030848,427641633,440902696,822593212,522303856,322754828,288079694,807209645,111668651,116180433,805525713,369444386,56305184,538549429,855064933,408481567,706513987,270603374,888874515,869737690,450119928,679238566,804805577,651180933,546799298,179149268,870230497,157803266,83687737,949485734,660162137,196609367,934814019,759805090,400707264,223692929,30684171,30657162,122464431,98740827,888156482,932064720,112249297,746200907,324630241,589132443,726576875,954976637,987095152,437453830,984659637,754518701,47401357,826027689,112861607,696470764,497956225,250361638,40151094,76721110,414608027,530157868,60168088,241724280,516804319,789824550,376501201,261319829,79852813,845029536,168948455,542422449,14235602,377668907,218851785,212574473,191651583,174624465,784685853,627701264,212661821,308722031,697066277,429594588,721056741,778453854,560478118,228266417,859346814,789370638,258032745,557936424,661224977,845620414,610644835,612842107,925041977,356438399,376285455,147688544,731950688,115172504,802214249,935517277,310280612,216317674,6811130,877125482,500440019,574835154,124878394,550028962,583967898,723291751,567003562,225111059,89921218,672118586,873138566,684564333,787539126,977891023,972424306,803353065,682495521,30664649,834892236,362493992,714130414,173532562,465697749,141265712,243276029,877786708,716734025,378511070,787117889,437447268,907685793,459332010,731397402,228400287,797848181,379570268,515174333,713434896,455781723,435508211,935521357,128010060,447063192,111481282,159554990,705858408,802837814,186918049,14211262,449205554,577063899,331605728,40607687,903447414,250388809,85199112,727934933,19819402,737738750,748359168,585552623,705998863,296457528,292850529,82104855,764232222,761748690,747471725,190349508,132581614,862776555,424920050,803726808,342432253,244109365,478743321,155570288,277342089,397066469,193109503,177573201,23990272,793806704,172909004,261384175,866948624,757717391,159233180,439520189,600281990,64851034,38555965,298352021,574701099,747664143,857430604,285806889,612144871,95039844,396611787,257703472,224736251,83002883,917241114,80729842,105051540,223545290,457325108,279454856,24300293,143966252,626241124,512045319,411457261,827348878,377352247,271003610,76666205,54530329,30813167,142207463,74463655,369088993,761084808,457882808,792088815,352488342,607341382,397201286,995246811,690333383,981464903,348384180,714175793,509096183,381704521,71735354,983062272,143313131,602197504,356557690,875904257,727559899,23449003,677711203,800309032,252381793,361266974,908061115,456967785,717194510,624337266,864886893,619148003,555972231,5477055,865071734,775071686,505039565,364911332,251055417,499592861,615768075,977792437,349551356,703946438,783331349,165483393,698578769,297880214,437879870,260968439,669721484,370669875,66247239,886984548,811793940,516038396,817865822,498572695,943421142,837565341,908425681,119044256,547665832,137534839,103148840,540847991,65688464,499761057,27059824,230501974,483800403,296810433,917404120,734121977,699187663,186584782,172717571,86726457,302130199,612316360,566743853,147520480,23015220,216176364,747064884,130340710,865946552,670821828,79909943,656573792,677793008,832709662,187348575,286238670,653637010,272813972,579202306,94904185,743379209,569493380,644544622,634508459,105574531,502558053,703406898,647758074,962272195,83284607,965863401,497259364,483381085,159655332,34538816,433148161,974686011,107120057,196493142,243291133,498769510,4836530,177043432,288160985,630621321,131003911,815108093,311394036,950098683,611209607,910131508,381327638,613395893,282701431,616368450,402151355,194702413,38052679,914259332,595959409,643201093,968790319,248828832,339428847,557301633,549089151,408261121,103416990,312744814,246476028,894005672,263608737,407261940,188991751,958992544,399285228,825545235,382384912,139924045,495860053,974145698,805712132,599381336,855570134,724691727,521303788,379569031,183242789,671808625,814845293,48407083,679303242,584070283,523192970,946237212,411732052,345406040,322468524,639275237,599284582,800533801,700471086,727416461,10646349,492237273,145429818,982399964,832905400,521347279,471822076,817001543,397427533,797624286,420764146,763017204,766372356,722384751,726567430,774578782,128260642,672475624,425308208,956113007,89513859,740594930,580138880,639667205,774884768,205489214,994271859,707609521,297564469,751385829,137169197,464456846,446813248,16481395,470790379,115439068,545338291,677667796,230042603,282517784,450162369,116261993,790169198,73185230,628968887,557278802,281653965,379589733,451536110,422027886,933840480,173784895,895692186,600569863,941119794,10215879,722807834,835492163,242776918,471338418,136475968,481661251,746462701,376190954,272905930,170095245,381369130,647118969,603040874,928132071,862521291,91068149,653564247,27842076,285536511,659725221,617737077,954436899,168513718,419016530,178923716,136026497,783626784,99515953,278362386,355847369,997042337,29368029,952263049,233454730,316982054,113570024,26207554,968217984,591884047,18878032,783454081,904676787,30739366,789798345,746284182,270239666,607211788,759243154,626598334,91658702,639320111,337945304,932367859,613650278,107997590,702807165,122004844,593441490,62197433,287199918,245293699,12722112,877184955,898432986,624931561,103056890,771997115,926269464,5763741,667314832,391004385,781014065,427434851,956300519,492892618,167240465,214073632,982787195,10319518,404419260,155105232,194495711,264545446,799886608,542645367,479334442,775761576,57802491,320181148,367246992,587614008,27562780,598852458,796874733,477062193,277717575,53846536,649588249,93453923,547541822,115579849,884448724,790583043,171861798,724941610,353339603,905963469,200578945,872685892,65382100,481429323,858172947,929689972,363876491,506850730,192345193,970974855,655083733,496938387,943565520,30430299,84996211,827142329,622243748,478512057,217544623,548579330,901558026,816107869,891740370,82871673,495353045,304166404,876944194,29414443,183011467,602176820,75044998,496160702,41105587,421458551,416296106,450322491,744653725,681915730,898554793,538866169,617376992,106669234,535714239,761545908,130970069,853658583,197823988,511052103,611251733,862433417,520167099,310018458,999882733,560597174,787976961,239963293,663077658,673553422,160398980,61719728,907509168,292685571,432853212,964295934,932154665,736209282,548515509,232338931,607730875,400997851,252498130,580580178,139074490,522004028,28035029,177336851,210189977,713195028,648991369,572857626,271280653,447127951,73200626,341918865,26734774,983046294,834047892,783805043,780122909,859993225,558066773,659588744,322961340,368878414,760185403,658645437,754656474,783945776,460373282,592278608,591327786,292328654,631039161,211855474,333519690,431699964,45606936,826648589,358700839,923901921,951097561,31316618,42107699,202808666,576235495,944026657,896387115,763640417,668123525,47734263,810258572,74337448,189425696,102543936,131741634,502139185,209922927,576592649,957633609,342223424,337587116,316032930,329784980,265595990,837041881,847276612,732795600,583374572,841799766,851325490,947815394,491923012,966879926,503167666,397040122,56035582,698358362,331780972,954061253,261279148,162053428,306861306,663044112,839054128,328827203,482497998,19400253,794872719,299172297,37847282,127134110,142208096,802237942,424067031,27389706,156543068,303960799,871240949,318951960,482766113,443006185,912249209,834645521,831641758,146299241,624676083,940588421,392857165,204355779,800946051,896673698,693944727,251680833,383865684,851729659,9983098,872687840,24063240,450398100,260258218,122784513,347027731,614886666,354990705,136993731,78544721,20843784,616963039,472935553,974327308,240566962,540589242,717953996,645018357,627506214,626049454,187037910,992319214,776264326,240035630,930975319,997394796,599178777,788636352,911620065,906719343,867809325,62328730,522049725,111704966,930168992,107558171,744715706,766145844,322096840,270317063,550810519,988667695,142946099,52655308,262877922,638877181,760519986,989345508,408626290,722609995,694873679,10119504,332139472,338325367,307320859,837887697,499571407,915199651,584953303,752336935,381815654,965237113,164752359,682005050,847305694,445027448,923056570,615081450,943963703,950340780,192205742,747006138,580204973,85684616,743803583,856536300,113007508,461178318,734084885,113976840,821577890,690964554,624577416,849457488,937341831,23622380,948536557,462654883,333962357,585100885,622456324,600842971,836813268,696425562,284627321,289012413,928078729,670433353,676092053,553135090,417881441,623384759,184419613,505305995,616873080,533795488,771316604,894659709,487626661,268008853,403508109,446192568,715247054,222823171,770437268,806337542,780721596,943314229,428368450,574249709,637985919,585236101,383388563,69291706,398619836,329708520,772410939,266372070,661249755,794151745,176021640,459387506,189239124,818818240,526519406,497648903,764804584,623974296,671683885,186423074,724153585,735011313,405755338,434072333,567659902,251285425,369665871,833885272,411331165,893374530,734959327,907969665,825132993,819975485,846464473,725757192,436552374,868431947,479946500,567103301,447018815,115878867,868553027,592664495,786976399,9166791,246026996,633107927,100931272,269850925,338146211,771288964,882148737,778444680,654572396,788265085,319640243,615889822,372312361,466545346,860362535,93420576,529726489,931798318,320111308,912582860,126491704,270945720,816787370,974737247,682815119,91858569,241107368,19526258,621889419,520122951,690972016,819011249,522929419,581756627,838405179,634923444,11633075,493093283,540124639,220732202,204842030,337883503,743716196,355989883,459776558,799678055,115312728,30094745,991445447,106659709,216198217,743143063,131899998,224565545,932843935,105523697,878471898,128652899,587573660,157719872,490957526,715754,189039628,482170186,121266080,717500197,917084264,594399104,798890367,37300408,545480202,301620109,379109076,348957515,922714159,46967549,808651347,982841914,480752775,975638418,139413479,382922882,273532342,101594318,246087982,896115013,59883031,62695901,423151147,430457162,288750955,900904073,809668786,619455361,192830460,724633787,715317963,15634820,310763081,564070910,667079481,64740307,315334936,152038527,187438671,278029857,316486674,414819197,244169574,38352232,120666598,849418710,807137265,910543722,353502954,269462765,937409008,935912162,481544618,19682838,958128854,787687576,324273785,518667812,518804963,661829701,833550543,655875882,579250879,281225255,752057652,192210898,365422560,495763205,321244755,359361314,987314628,107572808,492562803,246306520,709427437,394996809,448070840,516942057,776902713,262597457,274192146,589474171,567482968,712750695,102670030,463708507,208016240,308486403,986220607,83022592,952831975,892079264,623193347,195977817,252978558,987575845,215948550,884504692,253263870,432629440,358655417,497314021,822890688,629159363,528735091,844163282,792770688,873616296,509586056,725100002,987597705,486231443,994038437,171574119,734275360,651947420,106265119,57433494,512236469,633576071,125354499,493331399,457419472,678700087,193960834,952124856,843801012,563520037,947743059,181954268,343043237,3001117,957418529,74726316,592453528,330540451,83735188,776907170,648755177,288995238,209244402,118901675,629666477,467891595,793797606,152615685,722262801,622880311,303751319,944217658,392838702,297625842,783203950,872773836,855159619,210200531,811476109,737219381,47902070,144851125,263053337,453618266,946752311,992587162,588444116,228060468,984807268,495901798,469073466,8818137,551028176,748291406,988770034,203660417,115203345,982142330,443563763,721319422,211188289,526655356,155569943,846616834,879917958,959679456,111145334,25397869,65516896,711491162,800639067,900999039,268844715,878192432,337234235,310981130,773873624,944100328,439847431,563546563,432529045,697448108,462639908,950958530,920756860,107600851,26499318,346462698,459642445,628322340,318351795,292439813,382776490,962337925,487989369,336754940,427826292,183468905,715657404,474218282,138829244,698967687,675258797,226061761,867463339,994480676,285201003,836420358,918908541,928406582,115836197,620329400,741114145,936637442,246971298,448461687,927129495,390946091,151904385,110113161,553115973,390949073,325912072,270941889,28447959,213757237,337778689,530236183,566782883,454780825,956613828,546166261,432030917,561571335,320060926,571085509,919398906,762826007,749521773,820336121,517363885,156546620,754363835,831940061,647362373,183625008,759415866,739181445,414771343,41014455,700755004,402493963,278704903,37774617,394359162,315037678,194044866,571901643,538410830,498040099,805940809,939428439,424989675,571260849,628422087,182911642,501026094,250239248,141938430,97994201,930059515,623345391,832069712,17557648,229386209,253771437,107918293,329937332,515625587,913095516,968162638,449009954,99199382,315874149,108157516,958782611,338230961,310916425,478806302,161239032,363810556,867817051,302020341,594544942,396133072,705463772,870850657,515746342,927957338,210348084,836484636,635548860,726997875,123832995,396201245,321963609,477072797,907257761,911128874,858597688,609696820,828962321,183888367,459878143,477527263,614468015,407218934,662960264,140231825,744333896,958236143,510606722,732868367,961269521,828871132,301077147,942401605,303170656,360070086,168304711,48755035,337507407,863250534,922220989,802627671,837661574,834544566,757888960,701253820,937126457,744954999,595850165,352946234,653596774,496278313,19499493,982076387,389730744,279881729,712233995,432445966,330091358,503105966,658743793,563443841,581292075,512506831,100166031,748932782,724812717,632548969,918412127,16634739,609464578,123301859,376832269,268151658,815851993,278798734,245165116,294891752,327095552,985594252,252302326,827351663,698717959,484050433,625602963,404917720,23819308,822303356,563893404,97830135,107461738,93052080,250614093,206861090,336128288,457564227,280510382,602293534,365033457,662741752,292442351,316227381,120019703,704204620,214750670,958542649,633282929,774999229,941809677,167831173,949402305,582032345,605107841,229070827,316571311,865023876,296192904,559961787,426664661,91352335,101768431,288199605,33652646,964833819,30341256,262774210,666613397,634556946,26007151,385388084,881555857,862206727,530642756,562008185,883676662,226087354,551092409,565417478,413627112,46819124,774297754,578460779,445252868,83676143,300653641,379008804,742878560,977489767,917614965,442795120,64158165,888860570,87638708,976656728,186372829,462320111,629438312,268795108,746406448,152028387,106446309,186801565,622402393,479037032,665181047,859354557,894310048,179536173,130616985,553033642,346958692,101577474,317715841,553084997,267732098,410724146,66369627,9051229,195778457,996049638,37724909,34185477,876007474,917134440,524269810,231310558,663108668,469906415,529939988,141827977,106337916,519560661,266554623,123637707,444923677,229743519,437795916,540005807,979253634,593938674,973622636,950055170,37156666,766465400,525216705,259165544,217964796,897965492,751109291,565456578,674251976,410239606,504496321,813409093,246808791,152783894,431122981,181681081,171552889,551096742,782722582,362041517,164912795,790276532,473521307,796426218,711014104,699871484,213103259,370732451,677381918,972809991,471503057,277209248,919530230,754091823,811118162,501404039,387910749,457469634,158678524,105200925,921520444,862254647,579491909,763025936,788993999,522910736,312981593,777901604,37870392,566449613,184384066,89120113,619229549,871326267,724379411,395358411,277972522,956856710,57856642,719072900,550355146,990350617,404533909,621887590,644657601,891034371,363954352,462528877,701723516,313528213,517229974,808722011,629218582,330318264,484132934,75853166,244030355,100498586,547053072,761776308,455916627,537835749,416820652,696896168,776410553,805638970,827801745,811575797,627130425,23466885,969340527,665736716,248233087,250474300,781279861,463528680,258426820,907720182,214208209,151054828,949841908,534189446,778287926,593926876,299431730,892619781,474553628,508038818,26195679,930425199,85558785,723407599,631265590,419096046,991606183,883929124,584102499,401382061,897803992,121061403,768150247,826073768,730897743,871705611,493381255,242254724,883959283,34629406,778296589,953240917,250815857,570308920,112657644,720519967,677259007,849489362,209985259,26011548,835942864,548430222,931919930,430115071,198012676,874464388,237213974,767434657,429451380,206330671,412653052,646861175,307809303,753134199,504590032,156178713,699793546,544099511,164050017,185646898,600386900,146162018,521467804,340238509,187129040,197533041,665210442,927330853,222667610,523696723,230730266,446012138,992039890,8300915,284132069,713419072,947619752,865177945,456420156,859369491,998689082,845991325,452836110,866042171,136849970,461763427,753891898,77363677,598504351,724464507,7809512,397980952,924164000,697617046,864978329,866066508,695933414,721919690,617172525,626663115,63033252,72509488,818542372,172493030,141658162,181224475,426034636,79363961,153526585,596949867,618185059,448224525,97592834,930570143,613729514,954448365,683388242,366069684,410771675,465070856,929787351,936868840,254053512,698130352,684096122,670999343,350812354,734992736,514365465,48824684,94836175,149716490,254140851,955098935,217176278,967888856,529434786,443114259,23443824,564188856,665500209,955654747,390852422,944169450,119648328,188875807,354462071,577760366,148729278,484458461,659673101,697013456,289909285,529700323,974596348,355168380,153353646,313027690,111969490,181594759,322410900,60511994,308427898,742513075,860780776,210143574,348810666,612515537,76991509,965656187,509426579,994745941,266750683,590906591,938561592,413157808,698203827,729604909,658524755,936229527,523982483,222489048,507019133,134437749,577750062,460076831,490444038,530947917,337525050,456152084,694246956,676379162,16638406,895560303,496690748,368422050,449392525,751677875,413694210,262322489,983512215,127290321,143323071,870911553,881907746,323940868,200098066,947070975,119014474,483924582,943351892,275356603,876652295,248636352,697422579,397154977,241954245,873784528,845629631,490222511,851478100,989612191,480690518,473549421,695845167,279153607,841022579,530908116,695884184,368114731,675967518,31016465,582624651,432824950,240693388,606224169,806519414,605240,780811498,218107212,220463429,36228319,778066365,654931776,301439625,87626727,688789971,894601453,670868515,322908524,915398860,585065543,51644436,466501375,316700583,697450276,783633073,169999754,651877482,573074791,652233435,931433486,83439789,656835361,330425149,564730215,674537007,655471890,949076718,744158074,937719843,760217410,817053692,306534040,956948468,974375849,117912323,849929912,245690723,9416035,419633098,334547062,873832973,570901172,249359071,184790555,464730505,858663278,209550677,769795511,630903014,529172551,323806888,932616287,341541162,361441946,307970589,362567344,704552738,137603545,704039984,931021597,924148456,52369532,173167319,880462874,832107760,964153946,604230310,919419361,827280706,615861761,440192507,222125557,459822212,547463294,535786628,835585917,788477823,310317874,663937544,648517190,178843403,2978881,426767514,113312623,604132371,967945295,257677993,256853930,378613414,844148073,697017748,526240263,681776798,411749850,493324992,250642319,966000897,147050765,114446194,129015470,366565815,980899070,892943080,690998709,601975463,5571621,481203037,180350107,79278859,527651943,225247143,593443248,911931389,395773110,908986405,897002443,773735616,384547635,846511785,618924870,222591037,801781337,295898944,366267355,420724980,651528902,376438161,682189174,530643530,633021147,84725898,337651405,769644373,167057106,416172790,655392623,256936368,819114541,27325908,100107979,516644586,122511053,565093850,790485759,881887884,944112951,52906357,825871994,71312262,396267526,239925905,972951283,537175030,738079754,251204861,96436642,63777601,314738056,104040522,885681419,667747107,746328981,993829303,848518926,608523937,558751647,119168595,815463367,834670528,887264865,209543066,607061640,153796383,425675181,319619094,446331630,371647271,188054995,989886652,494966152,279424853,122078198,976365496,351235669,666817006,72298073,959918715,933376898,800587570,52844822,575196306,725055952,938220928,884406233,470102943,147503783,587939904,765215899,999801466,719537828,269330236,357875411,825793239,458037451,918874617,498194123,712899114,632627667,117482220,959262804,297958261,20121898,10259433,468444339,64024365,500860184,410477055,282092463,896253732,146168758,56111545,481987595,131119231,973851619,422937081,370795847,537613531,827722926,530590610,208205431,61651825,761123504,632232583,912554918,693213627,527015648,288439266,322096036,963044124,884369503,762728739,247310262,278005187,174368041,909120387,782340764,728838924,852304035,882151160,587360154,730531069,262218995,31738433,105182284,607876686,664079643,994599668,555842733,683894671,810853769,81603946,94400535,883930382,380766745,119538043,534748128,940372149,212842957,669727950,296509592,239710962,378430921,636059822,88374104,875960366,558661806,313274780,155133422,68731769,620676040,857630242,820398475,252202515,546696895,64002980,968375295,168491278,206282795,476901874,3811515,51394334,16741224,308402114,908353133,347250399,30569161,506748124,414236650,793918121,450727414,517650859,609679705,829290435,107971406,17256573,725889057,832795427,534279149,37104564,469970550,334599228,826025098,306753329,483937604,554907060,517845614,513399512,811053196,456426429,979071936,661441176,713607339,685756954,310792516,191971578,722424997,617841578,219932130,542481044,895001126,499398159,200048852,88929658,630135090,934341038,684265803,750704587,398782410,78961447,692292858,11032082,771926344,558395120,790641838,466030973,378698060,591201537,217598709,622090623,474773010,231813977,442413206,227970396,915529697,434583612,767557384,758471722,178598958,450578955,448564967,791416254,731467618,738789531,854684600,551781030,962090950,617898619,812283640,197607868,34221133,541653172,594845000,523449284,531245275,56989523,567393268,848659521,113917835,23183754,62553593,718979494,654844001,217519213,621143544,653314740,262034566,259589730,564827277,984177905,571007758,535135926,934007482,154134669,46276857,636662193,229040223,838656514,439411911,623644372,133770918,118583099,688948972,173642567,110933513,482655716,979744007,373456766,48562889,669494522,581888270,647148401,492337064,528654390,88810754,342961575,75057840,975594314,945204804,896045202,419328516,964746965,416208822,923976569,361191448,207433066,142990728,636344605,897162044,324591948,221811480,544761445,653085093,522005226,768884051,785967671,488676042,847116846,828883117,71908755,927715727,995860429,988063869,22220478,287466494,977585087,535116329,808729596,624500515,415233788,270145350,799590715,363293787,282104097,175657516,998324145,67853838,362693807,514359662,828457388,205394803,881727126,710192688,18763728,517718457,505511749,492549025,195309380,628829100,717112056,709026752,185193633,364455291,847440256,482764258,928669856,727771800,909077633,513196123,749235994,966548302,793538766,748342116,604018013,130016019,643214710,645584198,782790081,574455974,532328609,654581682,907615719,368429004,195346599,832473701,677336009,316340630,675804501,819801784,94154960,876108626,170479156,96311593,26773666,797757269,633495166,668246370,561279198,15391652,639221083,221842546,562146899,412237041,25732221,767714339,760116222,552822041,545960977,264582598,522385746,277650223,900359059,467598076,828454217,197666986,536424215,725559962,460379334,986598821,823713536,861338050,170294710,481923877,556841547,71038724,814959680,449958460,409483031,369832433,585373466,183658929,916844400,912354528,277341268,604867835,407976039,286875008,770479710,423951674,524255050,714874414,275019037,923820379,230631176,975896867,515106746,830126743,62256275,496709826,674033541,183229029,896732305,538244672,865140964,326083992,101365383,188622572,776939174,541120825,717716914,287777481,128231584,832712633,962158915,652822305,259846932,282938781,566598781,162683802,842894859,961773117,811746048,979670619,883014120,794471639,814484425,91198469,301675036,269571439,871947209,279364087,158144141,565647910,125435851,371926819,84815412,199774070,637773843,341080135,636163187,365500410,548989742,170960052,324979737,655814211,554682175,104494341,609235992,751040886,80765996,119004660,930505211,633010409,717683969,114495223,575939296,671006344,789366888,72482816,959405543,218139373,781703394,974044014,388537544,214217407,797269582,497813276,672588624,100228913,12610613,480381639,313953129,957200574,576796201,585281399,567802332,181994733,129325743,906233141,474145964,823154790,754751352,670105278,133047646,941348051,172729667,752635906,616754066,814362881,51351912,8521003,203124470,345167956,213027699,321587328,655899310,726229501,249511881,885537778,323568655,674533527,854558841,309461521,107125810,753152516,467597234,841629667,786969078,983737173,449773929,624377709,656269190,114886454,466459786,141596507,896379480,143407998,209454866,804930491,320352019,494268880,657906541,161083658,765555389,240477416,643314206,881769105,408689782,946421040,815075058,770955505,136227229,434031342,86811998,634121148,344927565,95905616,863463484,175638827,594473005,653867289,847302422,905754479,831246288,267728794,45281372,992194188,580521901,885362182,128113325,663971804,633718547,864162465,453770195,680922328,77934424,791371507,207389730,749816133,656119793,616418505,297271537,659692538,710965692,273943424,620245083,510693796,971674603,281804989,798720248,341717691,80497589,450861796,644386154,341968649,869419216,630585326,497187759,640266394,86543745,626642230,965240965,53533202,791185412,146628973,203286861,503912861,270536120,256473217,271991541,351908785,858331351,641863188,703665287,68213963,658366716,2947098,103373765,322633051,93846771,325145582,756430344,419792036,294830834,471703615,169977721,375444447,382815804,304644842,330170362,530861561,514622405,377516953,553063981,749180338,832298718,294206968,452388193,754787150,819975858,451709693,325599240,32047028,159512462,923770521,923367011,311867912,137694553,799289297,162770101,927572137,411666472,338657310,978805070,607636771,262233111,407896543,691774103,687265514,783080179,578690901,706093589,252851400,97846412,744064735,58213244,617715754,882360693,701220427,272767232,795949633,281940580,576861374,90197399,750941512,933616866,43209047,631804120,600624983,502865700,347049376,628460836,434596327,650859047,360639233,985710430,170826012,941896625,759404319,861523948,724907442,400598967,77927268,183555163,82897702,293037804,987488759,203548375,22556579,577622777,943554485,727277339,680244574,197736875,865233543,154595648,968677027,706896920,586445753,13101607,917909484,288248113,410651368,322924180,481742019,878739486,301479375,268692398,763514207,698259707,662334405,682854915,644331470,300695571,45194888,844466606,35435573,707089820,351472920,536209637,681603913,862405202,7603723,20450004,820788033,397619742,677692576,896322114,634359666,246486042,640321280,886433112,818254617,198532616,870605651,646184883,327890704,438569183,364380585,624902060,63375050,381703446,897560127,903288230,542351792,143745971,907002124,502614804,260466949,729521334,827102807,34223419,880521254,281744795,469449264,52363853,52097767,585145563,237120480,905415848,680015907,969123061,964404181,563045796,333219547,789556231,638406068,918664302,213092254,740938590,381785483,966640179,387628955,662565976,866444111,699722694,508943810,792638611,793307102,970104063,826766689,506416432,3624695,443183564,312329365,907388810,901161015,948724148,362928234,380480024,289805123,767370785,62659548,801639277,609048943,26804576,989024750,274007936,778983779,814306574,315177422,811826264,991853918,323582350,973313674,759005373,82441236,892050437,698308420,678383330,492881183,221350454,808369065,801413581,500512522,976705957,412675227,349322665,713258160,776502975,803331189,772391340,445933418,131731042,660234457,486620721,3991476,878640901,804861409,322961008,364058973,506421625,354103106,260831555,359056292,12618703,344608141,50477806,217298111,524150252,395850518,235142930,19270208,366761197,187697925,120685561,258450659,446634274,954913,154622141,186631946,33495801,181835443,338471174,808138529,285892973,437310030,371007759,10430738,652336595,96008232,34847604,826784106,864696066,304794421,918564215,282183879,10393336,567473423,326708726,832860641,817925464,816547758,426786760,636346220,217118148,790758484,89856602,946149627,420034479,792270972,600743238,514349511,71050762,104677203,860090592,205004338,630391823,462880311,793657339,4283891,598513367,458983926,411673788,354893353,712921767,716425891,842530849,965785236,311669452,108224705,560260153,633400565,545638190,790523771,318580210,668677123,910026008,881482632,42587322,437155518,792299597,36670825,84428155,929269243,944491355,528255018,629894526,512634493,445396258,186968777,320428001,924265341,860842034,296589615,520374634,171989322,457294725,967284733,679659893,63126637,603739686,812501999,671517513,916660987,858814345,246311854,164992964,165393390,8195350,483975089,509406823,114644779,685723887,53102426,617666448,207172258,623151847,532702135,768941501,429707160,198803488,779734593,642939667,53635336,960584207,116164597,197001309,536841269,368324673,630057303,792914276,386541987,994065976,627500870,573443769,599685896,966533706,301196854,759137421,371930700,775556523,767790141,20211256,379943099,792894374,824619763,946198358,373451745,596952378,752243809,114955307,925139828,268761837,860551136,818476649,578471809,348246100,576368335,52979524,120815665,592296500,119895268,98016105,291993453,23895805,206526983,441442575,847549272,724553294,374116154,782816485,550507082,420567331,976517503,555103342,946033733,886354425,216046746,283129306,85104325,312720425,877002932,383521365,765080455,599755664,894658473,474857680,780882948,311490118,74434897,433350723,35784547,128900492,973737505,168759145,139066955,353658242,869544707,778368564,590393084,926316480};

	int fact(int x)
	{
		int t = x / divide, res = fac[t];
		REP(i, t * divide + 1, x) res = res * (1ll * i) % MOD;
		return res;
	}
	void work()
	{
		if (!islian()) return;
		if (m < n - 1) return;
		ans = fact(m) * inv(fact(m - n + 1)) % MOD;
	}
}

signed main()
{
#ifdef CraZYali
	freopen("B.in", "r", stdin);
	freopen("B.out", "w", stdout);
#endif
	cin >> n >> m >> L >> R;
	REP(i, 2, n)
	{
		int x(read<int>()), y(read<int>());
		add(x, y);add(y, x);
		de[x]++;de[y]++;
	}
	depth[1] = 1;
	dfs(1);
	LOG = log2(n);
	REP(j, 1, LOG)
		REP(i, 1, n) grand[i][j] = grand[grand[i][j-1]][j-1];
	if (L == R && L == n - 1) cheat1::work();
	else if (n <= 5 && m <= 5) violence::work();
	cout << (ans + MOD) % MOD << endl;
	return 0;
}
