#include <stdio.h>
#include <string.h>

struct ChungKhoan;
void hienThiDSSV(struct ChungKhoan*, int);
void hienThiTenCot();


struct ChungKhoan {
	char ma[3];
	float giamocua;
	float giadongcua;
	float giatritrungbinh;
};




void hienthiTTChungKhoan(struct ChungKhoan ck) {
	printf("%s %.3f 	%.3f \n",
	ck.ma,ck.giamocua,ck.giadongcua);
}


int search(struct ChungKhoan* ds,int slsan, char x[3])
{
  int i;
  for (i = 0; i < slsan; i++)
    if (ds[i].ma == x)

      return i;
  return -1;
}



void docFile(struct ChungKhoan* ds,int* slsan) {
	FILE* fOut = fopen("data.txt", "r");
	
	int size;
	int i = 0;
	fscanf(fOut,"%d",&size);
	if(fOut) {
		for(;;) {
			struct ChungKhoan ck;
			fscanf(fOut, "%s %f 	%f \n",
			&ck.ma,&ck.giamocua,&ck.giadongcua);
			
			ds[i++] = ck;
			if(feof(fOut)) { 
				break;
			}
		}
	}
	*slsan = i;	
	
	fclose(fOut);
	
}

void hienThiTenCot() {
	printf("-----------------------------------------------------"
	"----------------------------------------------------------------\n");
	printf("%s %s 	%s \n", 
		"ID", "Giadaungay", "giacuoingay");
}


void hienThiDSCK(struct ChungKhoan* ds, int slsan) {
	hienThiTenCot();
	int i;
	for(i = 0; i < slsan; i++) {
		hienthiTTChungKhoan(ds[i]);
	}
	printf("-----------------------------------------------------"
	"----------------------------------------------------------------\n");
}


void timTheoMaCK(struct ChungKhoan* ds, int slsan) {
	char ten[20];
	printf("Nhap ma chung khoan: ");
	scanf("%s", ten);
	hienThiTenCot();
	int i, timSV = 0;
	for(i = 0; i < slsan; i++) {
		if(strcmp(ten, ds[i].ma) == 0) {
			hienthiTTChungKhoan(ds[i]);
			timSV = 1;
		}
	}
	if(timSV == 0) {
		printf("Khong co ma chung khoan nao %s trong danh sach!\n", ten);
	}
}

void timkiemMaCKcoxuhuongtang(struct ChungKhoan* ds, int slsan) {
	char ten[20];
	printf("danh sach chung khoan co xu huong tang : \n ");
	hienThiTenCot();
	int i, timSV = 0;
	for(i = 0; i < slsan; i++) {
		if(ds[i].giadongcua - ds[i].giamocua >0 ) {
			hienthiTTChungKhoan(ds[i]);
			timSV = 1;
		}
	}
	
	
}

void timkiemMaCKcosongaytangmax(struct ChungKhoan* ds, int slsan) {

	
	printf("Ma chung khoan co so ngay tang lon nhat chinh la : ");
	int i, timSV = 0;
	int dem=0;
	int d=0;
	
	for(i = 0; i < slsan; i++) {
		if(ds[i].ma == "ACB")
		{
			if(ds[i].giadongcua - ds[i].giamocua>0)
			{
				dem++;
			}
		}
	}
	
	
	int demarr[10];
	demarr[d] = dem;
	d++;
	
	
	for(i = 0; i < slsan; i++) {
		if(ds[i].ma == "PV2")
		{
			if(ds[i].giadongcua - ds[i].giamocua>0)
			{
				dem++;
			}
		}
	}
	demarr[d] = dem;
	d++;
	
	
	for(i = 0; i < slsan; i++) {
		if(ds[i].ma == "VNM")
		{
			if(ds[i].giadongcua - ds[i].giamocua>0)
			{
				dem++;
			}
		}
	}
	demarr[d] = dem;
	d++;
	
	
	for(i = 0; i < slsan; i++) {
		if(ds[i].ma == "HSG")
		{
			if(ds[i].giadongcua - ds[i].giamocua>0)
			{
				dem++;
			}
		}
	}
	
	demarr[d] = dem;
	d++;
	
	
	for(i = 0; i < slsan; i++) {
		if(ds[i].ma == "VIC")
		{
			if(ds[i].giadongcua - ds[i].giamocua>0)
			{
				dem++;
			}
		}
	}
	demarr[d] = dem;
	d++;
	
	for(i = 0; i < slsan; i++) {
		if(ds[i].ma == "FLC")
		{
			if(ds[i].giadongcua - ds[i].giamocua>0)
			{
				dem++;
			}
		}
	}

	demarr[d] = dem;
	d++;
	
	for(i = 0; i < slsan; i++) {
		if(ds[i].ma == "BID")
		{
			if(ds[i].giadongcua - ds[i].giamocua>0)
			{
				dem++;
			}
		}
	}
	demarr[d] = dem;
	d++;
	int vt;
	
	
	int max =0;
	for(int i=0;i<d;i++)
	{
		if(demarr[i]>max)
		{
			max = demarr[i];
			vt = i;
		}
	}
	if(vt == 0)
	{
		printf("ACB");
	}
		if(vt == 1)
	{
		printf("PV2");
	}
		if(vt == 2)
	{
		printf("VNM");
	}
		if(vt == 3)
	{
		printf("HSG");
	}
		if(vt == 4)
	{
		printf("VIC");
	}
		if(vt == 5)
	{
		printf("FLC");
	}
		if(vt == 6)
	{
		printf("BID");
	}
	
	printf("\n");
	
}	

int main() {
	struct ChungKhoan dsck[100];
	int slsan = 0;
	
	int luaChon;
	
	docFile(dsck,&slsan);
	printf("Thong Tin Thi Truong Chung Khoan Hien Thoi:\n");
	hienThiDSCK(dsck,slsan);
	int i;
				
	do {
		printf("=============== MENU ===============");
		printf("\n1. In thong thi truong chung khoan.");
		printf("\n2. Tim kiem theo ma chung khoan");
		printf("\n3. Tim kiem nhung ma chung khoan co xu huong tang");
		printf("\n4. Tim kiem ma chung khoan co so ngay tang lon nhat .");
		printf("\n0. Thoat chuong trinh");
		printf("\nBan chon ? ");
		
		scanf("%d", &luaChon);
		
	
	
		
		struct ChungKhoan ck;
		
		switch(luaChon) {
			case 0:
				printf("Pham Nguyen Gia Hoa + MSV : 20194566 ");
				break;
				
				
			case 1:
				hienThiDSCK(dsck,slsan);
				break;
				
			case 2:
				timTheoMaCK(dsck, slsan);
				break;
				
			case 3:
				timkiemMaCKcoxuhuongtang(dsck,slsan);

				break;
				
			case 4:
				timkiemMaCKcosongaytangmax(dsck,slsan);
				break;
				
				
				
			default:
				printf("Sai chuc nang, vui long chon lai!\n");
				break;
		}
		
	} while(luaChon);

	return 0;
}
