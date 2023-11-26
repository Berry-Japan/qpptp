/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you want to add, delete, or rename functions or slots, use
** Qt Designer to update this file, preserving your code.
**
** You should not define a constructor or destructor in this file.
** Instead, write your code in functions called init() and destroy().
** These will automatically be called by the form's constructor and
** destructor.
*****************************************************************************/

#define CONFIG	"/etc/pptp.conf"

int flag;
char ip[256], gw[256];

void Form1::ClearConfig(QString s)
{
    //system("sed -n '/\\["+s+"\\]/,/\\n/!p' -i /etc/pptp.conf");
    system("sed -n '/\\["+s+"\\]/,/mschapv2=./!p' -i "CONFIG"; sed -e '/^$/d' -i "CONFIG"; sed -e 's/mschapv2=./&\\n/g' -i "CONFIG);
}


void Form1::LoadConfig(QString s)
{
//grep 'user' /etc/ppp/peers/PPTP |cut -d ' ' -f2
/*    FILE *pp;
    pp=popen("grep 'user' /etc/ppp/peers/"+s+" |cut -d ' ' -f2", "r");
    if (pp) {
	i=fread(buff, sizeof(char), 255, pp);
	buff[i-1]=0;
	lineEdit2->setText(QString::fromUtf8(buff));
	pclose(pp);
    }*/
    char buff[256];
    FILE *fp;
/*    fp=fopen("/etc/ppp/peers/"+s, "r");
    if (fp) {
	while (fgets(buff, 255, fp)) {
//	    printf(buff);
	    if (!strncmp(buff, "user \"", 6)) {
		buff[strlen(buff)-2]=0;
		lineEdit2->setText(QString::fromUtf8(&buff[6]));
	    }
	    if (!strcmp(buff, "require-mppe-128")) {
	    }
	}
	fclose(fp);
    }*/

    fp=fopen(CONFIG, "r");
    if (fp) {
	while (fgets(buff, 255, fp)) {
	    if (buff[0]=='[' && buff[s.length()+1]==']') {
		//printf("%s",buff);
		if (!strncmp(&buff[1], s.data(), s.length())) break;
	    }
	}
	while (fgets(buff, 255, fp)) {
	    if (buff[0]=='[') break;
	    if (!strncmp(buff, "server=", 7)) {
		buff[strlen(buff)-1]=0;
		lineEdit1->setText(QString::fromUtf8(&buff[7]));
	    } else if (!strncmp(buff, "user=", 5)) {
		buff[strlen(buff)-1]=0;
		lineEdit2->setText(QString::fromUtf8(&buff[5]));
	    } else if (!strncmp(buff, "passwd=", 7)) {
		buff[strlen(buff)-1]=0;
		lineEdit3->setText(QString::fromUtf8(&buff[7]));
	    } else if (!strncmp(buff, "savepw=", 7)) {
		if (buff[7]=='0') checkBox4->setChecked(false);
		else checkBox4->setChecked(true);
	    } else if (!strncmp(buff, "dns=", 4)) {
		if (buff[4]=='0') checkBox1->setChecked(false);
		else checkBox1->setChecked(true);
	    } else if (!strncmp(buff, "pdns=", 5)) {
		buff[strlen(buff)-1]=0;
		lineEdit4->setText(QString::fromUtf8(&buff[5]));
	    } else if (!strncmp(buff, "sdns=", 5)) {
		buff[strlen(buff)-1]=0;
		lineEdit5->setText(QString::fromUtf8(&buff[5]));
	    } else if (!strncmp(buff, "mppe=", 5)) {
		if (buff[5]=='0') checkBox2->setChecked(false);
		else checkBox2->setChecked(true);
	    } else if (!strncmp(buff, "mppebit=", 8)) {
		if (buff[8]=='4') radioButton1->setChecked(false);
		else radioButton1->setChecked(true);
	    } else if (!strncmp(buff, "mschap=", 7)) {
		if (buff[7]=='0') checkBox5->setChecked(false);
		else checkBox5->setChecked(true);
/*	    } else if (!strncmp(buff, "chap=", 5)) {
		if (buff[5]=='0') checkBox6->setChecked(false);
		else checkBox6->setChecked(true);
	    } else if (!strncmp(buff, "eap=", 4)) {
		if (buff[4]=='0') checkBox7->setChecked(false);
		else checkBox7->setChecked(true);*/
	    } else if (!strncmp(buff, "mschapv2=", 9)) {
		if (buff[9]=='0') checkBox3->setChecked(false);
		else checkBox3->setChecked(true);
	    }
	}
	fclose(fp);
    }
}


void Form1::SaveConfig(QString s, QString u, QString p)
{
    int n;
    char buff[256];
    FILE *fp, *pp;

    // 接続情報を保存
    ClearConfig(s);
    fp=fopen(CONFIG, "a");
    if (fp) {
	fprintf(fp, "[%s]\n", s.data());
	fprintf(fp, "server=%s\n", lineEdit1->text().data());
	fprintf(fp, "user=%s\n", u.data());
	if (checkBox4->isChecked()) fprintf(fp, "passwd=%s\n", p.data());
	fprintf(fp, "savepw=%d\n", checkBox4->isChecked()?1:0);
/*	fprintf(fp, "#dhcp=0\n");
	fprintf(fp, "#ipaddress=192.168.1.99\n");
	fprintf(fp, "#defaultgw=192.168.1.1\n");*/
	fprintf(fp, "dns=%d\n", checkBox1->isChecked()?1:0);
	fprintf(fp, "pdns=%s\n", lineEdit4->text().data());
	fprintf(fp, "sdns=%s\n", lineEdit5->text().data());
	fprintf(fp, "mppe=%d\n", checkBox2->isChecked()?1:0);
	fprintf(fp, "mppebit=%d\n", radioButton1->isChecked()?128:40);
	fprintf(fp, "mschap=%d\n", checkBox5->isChecked()?1:0);
//	fprintf(fp, "chap=%d\n", checkBox6->isChecked()?1:0);
//	fprintf(fp, "eap=%d\n", checkBox7->isChecked()?1:0);
	fprintf(fp, "mschapv2=%d\n\n", checkBox3->isChecked()?1:0);
	fclose(fp);
    }

#if 0
    fp=fopen("/etc/ppp/peers/"+s, "w");
    //fp=fopen("/etc/ppp/peers/PPTP", "w");
    if (fp) {
	/*fprintf(fp, "noauth\n");
	fprintf(fp, "lock\n");
	fprintf(fp, "ipparam \"%s\"\n", s.data());*/
	fprintf(fp, "debug\nnoauth\nnodetach\nnoipdefault\ndefaultroute\n");
	fprintf(fp, "user \"%s\"\n", u.data());
	if (checkBox2->isChecked()) {
	    if (radioButton1->isChecked()) fprintf(fp, "require-mppe-128\n");
	    else fprintf(fp, "require-mppe-40\n");
	}
	//fprintf(fp, "require-mppe\nrequire-mppe-40\nrequire-mppe-128\n");
	//if (checkBox3->isChecked()) fprintf(fp, "require-mschap-v2\n");
	fclose(fp);
    }
#endif

    // パスワード設定
    //grep '"lxplaza"' /etc/ppp/chap-secrets |cut -f3
    pp=popen("grep '\""+u+"\"' /etc/ppp/chap-secrets |cut -f3", "r");
    if (pp) {
	n=fread(buff, sizeof(char), 255, pp);
	//printf("%s,%d",buff,n);
	if (n) {
	    // 登録済み
	    buff[n-2]=0;
	    //printf("%s",&buff[1]);
	    if (strcmp(&buff[1], p)) {
		// パスワードが変更されてる
		system("sed -e 's/^\""+u+"\".*/\""+u+"\"\t*\t\""+p+"\"\t*/' -i /etc/ppp/chap-secrets");
	    }
	} else {
	    fp=fopen("/etc/ppp/chap-secrets", "a");
	    if (fp) {
		fprintf(fp, "\"%s\"\t*\t\"%s\"\t*\n", u.data(), p.data());
		fclose(fp);
	    }
	}
	pclose(pp);
    }
}


#include <qtimer.h>
void Form1::init()
{
    int n;
    char buff[256];
    FILE *pp;

    // DNS
    pp=popen("cat /etc/resolv.conf | grep nameserver | cut -d ' ' -f 2 | tail -n 2 | head -n 1", "r");
    if (pp) {
	n=fread(buff, sizeof(char), 255, pp);
	if (buff[0]>='0' && buff[0]<='9') buff[n-1]=0;
	else buff[0]=0;	// resolv.conf がない時に
	lineEdit4->setText(QString::fromUtf8(buff));
	pclose(pp);
    }
    pp=popen("cat /etc/resolv.conf | grep nameserver | cut -d ' ' -f 2 | tail -n 1", "r");
    if (pp) {
	n=fread(buff, sizeof(char), 255, pp);
	if (buff[0]>='0' && buff[0]<='9') buff[n-1]=0;
	else buff[0]=0;	// resolv.conf がない時に
	lineEdit5->setText(QString::fromUtf8(buff));
	pclose(pp);
    }

    // name
    //pp=popen("ls -1 /etc/ppp/peers/", "r");
    pp=popen("cat "CONFIG" |grep \"^\\[.*\\]$\"|sed -e \"s/\\[//; s/\\]//\"", "r");
    if (pp) {
	while (fgets(buff, 255, pp)) {
	    buff[strlen(buff)-1]=0;
	    comboBox1->insertItem(QString::fromUtf8(buff));
	}
	pclose(pp);
    }

    // タイマー設定
    QTimer * counter = new QTimer( this );
    connect( counter, SIGNAL(timeout()),
             this, SLOT(updateStat()) );
    counter->start( 1000 );

    // 何もしていない
    flag=0;
}


#include <qmessagebox.h>
#include <arpa/inet.h>
//#include <sys/socket.h>
//#include <sys/types.h>
void Form1::pconnect()
{
    int n;
    char buff[256];
    FILE *fp;

    // DNS設定
    if (checkBox1->isChecked() && (!lineEdit4->text().isEmpty() || !lineEdit5->text().isEmpty())) {
	/*FILE *pp=popen("grep 'nameserver[ \t]*"+lineEdit4->text()+"$' /etc/resolv.conf", "r");
	if (pp) {
	    n=fread(buff, sizeof(char), 255, pp);
	    if (!n) {
		fp=fopen("/etc/resolv.conf", "a");
		fprintf(fp, "nameserver %s\n", lineEdit4->text().data());
		fclose(fp);
	    }
	    fclose(pp);
	}
	pp=popen("grep 'nameserver[ \t]*"+lineEdit5->text()+"$' /etc/resolv.conf", "r");
	if (pp) {
	    n=fread(buff, sizeof(char), 255, pp);
	    if (!n) {
		fp=fopen("/etc/resolv.conf", "a");
		fprintf(fp, "nameserver %s\n", lineEdit5->text().data());
		fclose(fp);
	    }
	    fclose(pp);
	}*/
	fp=fopen("/etc/resolv.conf.qpptp", "w");
	if (!lineEdit4->text().isEmpty()) {
		struct sockaddr_in dst_sockaddr = {0};
		dst_sockaddr.sin_family = AF_INET;
		int r = inet_pton(AF_INET, lineEdit4->text().data(), &dst_sockaddr.sin_addr);
		if (r>0) {
			fprintf(fp, "nameserver %s\n", lineEdit4->text().data());
		} else {
			QMessageBox::about(this, tr("Error"), tr("Primary DNS is invalid: "+lineEdit4->text()));
			return;
		}
	}
	if (!lineEdit5->text().isEmpty()) {
		struct sockaddr_in dst_sockaddr = {0};
		dst_sockaddr.sin_family = AF_INET;
		int r = inet_pton(AF_INET, lineEdit5->text().data(), &dst_sockaddr.sin_addr);
		if (r>0) {
			fprintf(fp, "nameserver %s\n", lineEdit5->text().data());
		} else {
			QMessageBox::about(this, tr("Error"), tr("Secondary DNS is invalid: "+lineEdit5->text()));
			return;
		}
	}
	fclose(fp);
    }

// 正しいコマンド
// pppd debug noauth nodetach noipdefault defaultroute name nakata1 require-mppe require-mppe-40 require-mppe-128 pty "/usr/sbin/pptp 220.0.147.8 --nolaunchpppd --loglevel 2"
// route add -net 192.168.150.0 netmask 255.255.255.0 dev ppp0
// (windows2003 server) pppd debug nodetach name aect001 remotename PPTP require-mppe-128 file /etc/ppp/options.pptp ipparam w2003 pty "/usr/sbin/pptp 221.186.133.248 --nolaunchpppd --loglevel 2"
//pppd debug noauth nodetach noipdefault defaultroute name USER require-mppe require-mppe-40 require-mppe-128 pty "/usr/sbin/pptp IPADR --nolaunchpppd --loglevel 2"

    // 設定を保存
    SaveConfig(comboBox1->currentText(), lineEdit2->text(), lineEdit3->text());
    // PPTPコマンド実行
    //QString s = "pppd debug noauth nodetach noipdefault defaultroute file /etc/ppp/options.pptp name "+lineEdit2->text();
    QString s = "pppd nodetach debug lock noauth nobsdcomp nodeflate noipdefault defaultroute name "+lineEdit2->text();
    if (checkBox2->isChecked()) {
	//s+=" require-mppe require-mppe-40 require-mppe-128";
	if (radioButton1->isChecked()) s+=" +mppe +mppe-128";
	else s+=" +mppe +mppe-40";
	//if (radioButton1->isChecked()) s+=" require-mppe require-mppe-128";
	//else s+=" require-mppe require-mppe-40";
    }
    //if (checkBox3->isChecked()) s += " remotename "+lineEdit2->text()+" +mschap-v2";
    if (!checkBox3->isChecked()) s += " refuse-mschap-v2";
    if (!checkBox5->isChecked()) s += " refuse-mschap";
    /*if (!checkBox6->isChecked())*/ s += " refuse-chap";
    /*if (!checkBox7->isChecked())*/ s += " refuse-eap";
    s+=" pty \"/usr/sbin/pptp "+lineEdit1->text()+" --nolaunchpppd --loglevel 2\"";
    //QString s = "pppd debug noauth nodetach noipdefault defaultroute name "+lineEdit2->text()+" require-mppe require-mppe-40 require-mppe-128 pty \"/usr/sbin/pptp "+lineEdit1->text()+" --nolaunchpppd --loglevel 2\"";
    system("echo "+s);
    system("/usr/sbin/"+s+" &");
//pppd call test logfd 1 updetach; echo $? $$;

    // 接続を開始した(IP取得はupdateStatで)
    flag=1;
}


void Form1::pdconnect()
{
	system("[ -e /etc/resolv.conf.qpptp-orig ] && mv /etc/resolv.conf.qpptp-orig /etc/resolv.conf");
	reset_route();	// 接続中ならルート設定を直す

	// busybox's ps と普通の ps は出力が異なる
	system("kill `ps ax|grep 'pptp:'|grep -v 'grep'|cut -c 1-6`");
	//system("/usr/bin/killall -KILL pppd pptp");

//	system("/usr/bin/killall pppd");
//	system("kill -KILL `cat /var/run/ppp0.pid`");
	//system("kill -TERM `ps aux|grep 'pptp: G'|grep -v 'grep'|cut -d ' ' -f2`");
	//system("kill -TERM `ps aux|grep 'pptp: G'|grep -v 'grep'|cut -c 1-6`");
	sleep(1);
}


void Form1::ClearForm()
{
    lineEdit1->clear();
    lineEdit2->clear();
    lineEdit3->clear();
}


void Form1::nchange()
{
    //ClearForm();
    LoadConfig(comboBox1->currentText());
}


void Form1::addname()
{
    comboBox1->setCurrentText("");
    ClearForm();
}


void Form1::delname()
{
    unlink("/etc/ppp/peers/"+comboBox1->currentText());
    ClearConfig(comboBox1->currentText());
    comboBox1->removeItem(comboBox1->currentItem());
    ClearForm();
    nchange();
}


// 接続確認
void Form1::updateStat()
{
    int n;
    char buff[256];

    // PPP接続を確認
    //FILE *pp=popen("cat /proc/net/dev |grep ppp|cut -d ':' -f1", "r");
    FILE *pp=popen("ps aux|grep 'pptp:'|grep -v 'grep'", "r");
    if (pp) {
	n=fread(buff, sizeof(char), 255, pp);
	fclose(pp);

	if (n>3) {
	    // 接続中
	    buff[n-1]=0;
	    if (strstr(buff, "pptp: G")) pushButton4->setEnabled(true);
	    pushButton3->setEnabled(false);
	} else {
	    // 切断中
	    pushButton3->setEnabled(true);
	    pushButton4->setEnabled(false);

	    reset_route();	// 接続中ならルート設定を直す
	}
    }

    if (flag==1 || flag==2) {
	// 接続できたか？ or 接続が切れたか？ (次のIPアドレス確認のため)
	n=0;
	pp=popen("cat /proc/net/dev |grep ppp| cut -d ':' -f1|tail -1", "r");
	if (pp) {
	    n=fread(buff, sizeof(char), 255, pp);
	    fclose(pp);
	}
	if (n<3) return;	// デバイスがない
	// 取得したIPアドレス
	//ifconfig eth0 |egrep -o 'addr:[0-9.]+' | cut -b 6-
	pp=popen("/sbin/ifconfig `cat /proc/net/dev |grep ppp| cut -d ':' -f1|tail -1` |egrep -o 'addr:[0-9.]+' | cut -b 6-", "r");
	if (pp) {
	    n=fread(ip, sizeof(char), 255, pp);
	    ip[n-1]=0;
	    fclose(pp);
	    if (n<7) {
		// IPアドレスを取得できていない
		if (flag==2) pdconnect();	// 接続が切れちゃったので切断
		return;
	    }
	}
	if (flag==2) return;

	// デフォルトゲートウェイ取得
	//route -n |grep @ComboBox1 |grep UG | tr -s " " |cut -d " " -f 2
	pp=popen("/sbin/route -n |grep UG| tr -s ' ' |cut -d ' ' -f 2", "r");
	if (pp) {
	    n=fread(gw, sizeof(char), 255, pp);
	    gw[n-1]=0;
	    fclose(pp);
	}
	// routeコマンド実行
	//system("/sbin/route add -net "+lineEdit1->text()+" netmask 255.255.255.255 gw "+QString::fromUtf8(gw));
	//system("/sbin/route add -net 0.0.0.0 netmask 0.0.0.0 gw "+QString::fromUtf8(ip));
	system("/sbin/route add -host "+lineEdit1->text()+"/32 gw "+QString::fromUtf8(gw));
	system("echo route add default gw "+QString::fromUtf8(ip));
	system("/sbin/route add default gw "+QString::fromUtf8(ip));
	system("[ -e /etc/resolv.conf.qpptp ] && (mv /etc/resolv.conf /etc/resolv.conf.qpptp-orig; mv /etc/resolv.conf.qpptp /etc/resolv.conf)");
	// 接続中
	flag=2;
    }
}


void Form1::reset_route()
{
    // 接続中か
    if (flag==2) {
	//system("/sbin/route del -net 0.0.0.0 netmask 0.0.0.0 gw "+QString::fromUtf8(ip));
	system("/sbin/route del default gw "+QString::fromUtf8(ip));
	//system("/sbin/route del -net "+lineEdit1->text()+" netmask 255.255.255.255 gw "+QString::fromUtf8(gw));
	system("/sbin/route del -host "+lineEdit1->text()+"/32 gw "+QString::fromUtf8(gw));

	flag=0;	// 何もしていない
    }
}


void Form1::setdns()
{
    if (checkBox1->isChecked()) {
	lineEdit4->setEnabled(true);
	lineEdit5->setEnabled(true);
    } else {
	lineEdit4->setEnabled(false);
	lineEdit5->setEnabled(false);
    }
}
