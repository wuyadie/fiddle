#include "stdafx.h"

void packet_handler(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data)
{
	struct tm *ltime;
	char timestr[16];
	ip_header *ih;
	udp_header *uh;
	u_int ip_len;
	u_short sport, dport;
	time_t local_tv_sec;

	/* ��ʱ���ת���ɿ�ʶ��ĸ�ʽ */
	local_tv_sec = header->ts.tv_sec;
	ltime = localtime(&local_tv_sec);
	strftime(timestr, sizeof timestr, "%H:%M:%S", ltime);

	/* ���IP���ݰ�ͷ����λ�� */
	ih = (ip_header *)(pkt_data +
		14); //��̫��ͷ������Ϊ14

			 /* ���UDP�ײ���λ�� */
	ip_len = (ih->ver_ihl & 0xf) * 4;
	uh = (udp_header *)((u_char*)ih + ip_len);

	/* �������ֽ�����ת���������ֽ����� */
	sport = ntohs(uh->sport);
	dport = ntohs(uh->dport);

	//��ӡip�Ͷ˿�  4Ԫ��
	if (strcmp_ip(ih->saddr, ipv4) || strcmp_ip(ih->daddr, ipv4)) {    //ֻ����������������ݰ�
																	   /* ��ӡ���ݰ���ʱ����ͳ��� */
		printf("%s.%.6d len:%d ", timestr, header->ts.tv_usec, header->len);
		printf("%d.%d.%d.%d  %d -> %d.%d.%d.%d  %d\n",
			ih->saddr.byte1,
			ih->saddr.byte2,
			ih->saddr.byte3,
			ih->saddr.byte4,
			sport,
			ih->daddr.byte1,
			ih->daddr.byte2,
			ih->daddr.byte3,
			ih->daddr.byte4,
			dport);
	}
	else {
		//printf("\n");
	}


}