/* $nsh: externs.h,v 1.12 2003/03/24 19:45:23 chris Exp $ */
/*
 * nsh externs and more
 */

#define NO_ARG(x) (strcasecmp(x, "no") == 0) /* absolute "no" */
#define CMP_ARG(x,y) (strncasecmp(x, y, strlen(y)) == 0) /* mabye arg y */

struct rtdump {
	char *buf;	/* start of routing table */
	char *lim;	/* end of routing table */
};

extern char *__progname, *vers;
extern int verbose, editing, bridge;
extern pid_t pid;

/* conf.c */
int conf(FILE *);
int default_mtu(char *);
int conf_routes(FILE *, char *, int, int);

/* routepr.c */
char *netname(in_addr_t, in_addr_t);
void routepr(u_long, int);

/* alignment constraint for routing socket */
#define ROUNDUP(a) \
	((a) > 0 ? (1 + (((a) - 1) | (sizeof(long) - 1))) : sizeof(long))
#define ADVANCE(x, n) (x += ROUNDUP((n)->sa_len))

/* routesys.c */
#define FLUSH 0
struct rtdump *getrtdump(int);
void freertdump(struct rtdump *);
int monitor(void);
void flushroutes(int, int);
void bprintf(FILE *, int, u_char *);
extern char ifnetflags[];
extern char routeflags[];
extern char addrnames[];
extern char metricnames[];

/* commands.c */
#define DEFAULT_EDITOR	"/usr/bin/vi"
#define PFCONF_TEMP	"/var/run/pf.conf"
#define NSHRC_TEMP	"/var/run/nshrc"
#define NSHRC		"/etc/nshrc"
#define PFCTL		"/sbin/pfctl"
#define SAVESCRIPT	"/usr/local/bin/save.sh"
void command(int);
int cmdrc(char rcname[FILENAME_MAX]);
int load_nlist(void);
char *iprompt(void);
char *cprompt(void);
char *pprompt(void);

/* ieee80211.c */
#define NWID 0
#define NWKEY 1
#define DEFAULT_POWERSAVE 100	/* 100 ms */
const char *get_string(const char *, const char *, u_int8_t *, int *);
int get_nwinfo(char *, char *, int, int);
int get_nwpowersave(int, char *);
void make_string(char *str, int, const u_int8_t *buf, int);
int intnwkey(char *, int, int, char **);

/* stats.c */
extern char *tcpstates[];
void rt_stats(u_long);
void tcp_stats(u_long);
void udp_stats(u_long);
void ip_stats(u_long);
void icmp_stats(u_long);
void igmp_stats(u_long);
void ah_stats(u_long);
void esp_stats(u_long);
void ipip_stats(u_long);
void ipcomp_stats(u_long);

/* mbuf.c */
void mbpr(u_long, u_long, u_long);

/* kread.c */
int kread(u_long, char *, int);
char *plural(int);
char *plurales(int);

/* genget.c */
int isprefix(char *, char*);
char **genget(char *, char **, int);
int Ambiguous(void *);

/* rate.c */
#define TBR_RATE 1		/* request for TBR token rate */
#define TBR_BUCKET 2		/* request for TBR bucket size */
int intrate(char *ifname, int, int, char**);
u_int size_bucket(char *, u_int);
u_int autosize_bucket(char *, u_int);
u_long get_tbr(char *, int);
u_long atobps(const char *);
u_long atobytes(const char *);

/* route.c */
#define NO_NETMASK 0
#define ASSUME_NETMASK 1
int route(int, char**);
void show_route(char *);
#ifdef _IP_T_
ip_t parse_ip(char *, int);
int ip_route(ip_t *, ip_t *, u_short);
#endif

/* if.c */
#define IFDATA_MTU 1		/* request for if_data.ifi_mtu */
#define IFDATA_BAUDRATE 2	/* request for if_data.ifi_baudrate */
#define MBPS(bps) (bps / 1000 / 1000)
#define ROUNDMBPS(bps) ((float)bps == ((bps / 1000 / 1000) * 1000 * 1000))
#define ROUNDKBPS(bps) ((float)bps == ((bps / 1000) * 1000))
#define ROUNDKBYTES(bytes) ((float)bytes == ((bytes / 1024) * 1024))
int is_valid_ifname(char *);
int show_int(char *);
int get_ifdata(char *, int);
int get_ifflags(char *, int);
int set_ifflags(char *, int, int);
u_int32_t in4_netaddr(u_int32_t, u_int32_t);
u_int32_t in4_brdaddr(u_int32_t, u_int32_t);
int intip(char *, int, int, char **);
int intmtu(char *, int, int, char **);
int intmetric(char *, int, int, char **);
int intvlan(char *, int, int, char **);
int intflags(char *, int, int, char **);
int intlink(char *, int, int, char **);
int intnwid(char *, int, int, char **);
int intpowersave(char *, int, int, char **);

/* version.c */
int version(void);

/* compile.c */
extern char compiled[], compiledby[], compiledon[], compilehost[];

/* editing.c */
void inithist(void);
void endhist(void);
void initedit(void);
void endedit(void);

/* bridge.c */
long bridge_cfg(int, char *, int);
int bridge_confaddrs(int, char *, char *, FILE *);
int bridge_rules(int, char *, char *, char *, FILE *);
int bridge_list(int, char *, char *, char *, int, int);
int bridge_addrs(int, char *, char *, char *);
int set_ifflag(int, char *, short);
int clr_ifflag(int, char *, short);
int is_bridge(int, char *);
int brport(char *, int, int, char **);
int brval(char *, int, int, char **);
int brrule(char *, int, int, char **);
int brstatic(char *, int, int, char **);
int brpri(char *, int, int, char **);
void flush_bridgedyn(char *);
void flush_bridgeall(char *);
void flush_bridgerule(char *, char*);

/* tunnel.c */
int inttunnel(char *, int, int, char **);
int settunnel(int, char *, char *, char *);
int deletetunnel(int, char *);

/* media.c */
#define DEFAULT_MEDIA_TYPE	"autoselect"
void media_status(int, char *, char *);
void media_supported(int, char *, char *, char *);
int phys_status(int, char *, char *, char *, int, int);
int intmedia(char *, int, int, char **);
int intmediaopt(char *, int, int, char **);
int conf_media_status(FILE *, int, char *);

