#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <stdint.h>

int main(int argc, char *argv[])
{

    int type, bitNumber;
    unsigned long long pageSize;

    if (argc < 4)
    {
        printf("Invalid command line format! type, bitNumber, and pageSize\n");
        exit(0);
    }

    type = atoi(argv[1]);
    bitNumber = atoi(argv[2]);
    pageSize = atoi(argv[3]);

    if (bitNumber < 8 || bitNumber > 63)
    {
        printf("Please enter a number from 8 to 63");
        exit(0);
    }

    if (type == 1)
    {
        printf("SINGLE-LEVEL LINEAR PAGE TABLE.\n");
        unsigned long long kBytes = (unsigned long long)(pow(2, bitNumber)) / (unsigned long long)(pow(1024, 1));
        unsigned long long gBytes = kBytes / (unsigned long long)(pow(1024, 2));
        printf("size of the memory: %llu GB\n", gBytes);

        if (kBytes < pageSize)
        {
            printf("Memory size is shorter than page size.");
            exit(0);
        }
        unsigned long long newBytes = kBytes * 1024;
        unsigned long long repageSize = pageSize * 1024;
        unsigned long long ptEntries = newBytes / repageSize;

        printf("total number of pages: %llu \n", ptEntries);
        printf("total number of PTE(page table entries): %llu \n", ptEntries);
        unsigned long long ptableSize = ptEntries * 4;
        printf("size of page table: %llu B\n", ptableSize);
        int vpN = log2(ptEntries);
        printf("number of bits for VPN: %llu \n", vpN);
        int offset = bitNumber - vpN;
        printf("number of bits for page offset: %llu \n", offset);

        int a[bitNumber], b[vpN], c[offset];
        int n, i, j, k;
        // Enter decimal Number
        printf("Enter a decimal virtual address:\n");
        scanf("%d", &n);

        if (n > pow(2, bitNumber))
        {
            printf("Virtual address is too large for the memory size.\n");
            exit(0);
        }

        unsigned dvpN = n / (pageSize * 1024);

        printf("VPN of the address: %u \n", dvpN);

        int pOffset = n % (pageSize * 1024);

        printf("page offset of the address: %d\n", pOffset);

        for (i = 0; n > 0; i++)
        {
            a[i] = n % 2;
            n = n / 2;
        }

        while (i < bitNumber)
        {
            a[i] = 0;
            i++;
        }
        printf("input address in binary: ");

        for (i = i - 1; i >= 0; i--)
        {
            printf("%d", a[i]);
        }
        // VPN address in binary
        for (j = 0; dvpN > 0; j++)
        {
            b[j] = dvpN % 2;
            dvpN = dvpN / 2;
        }

        while (j < vpN)
        {
            b[j] = 0;
            j++;
        }
        printf("\nVPN of the address in binary: ");

        for (j = j - 1; j >= 0; j--)
        {
            printf("%d", b[j]);
        }

        // offset address in binary

        for (k = 0; pOffset > 0; k++)
        {
            c[k] = pOffset % 2;
            pOffset = pOffset / 2;
        }

        while (k < offset)
        {
            c[k] = 0;
            k++;
        }
        printf("\npage offset of the address in binary: ");

        for (k = k - 1; k >= 0; k--)
        {
            printf("%d", c[k]);
        }
    }
    else if (type == 2)
    {
        printf("TWO-LEVEL TREE STRUCTURE PAGE TABLE.\n");
        unsigned long long kBytes = (unsigned long long)(pow(2, bitNumber)) / (unsigned long long)(pow(1024, 1));
        unsigned long long gBytes = kBytes / (unsigned long long)(pow(1024, 2));
        if (kBytes < pageSize)
        {
            printf("Memory size is shorter than page size.");
            exit(0);
        }

        printf("size of the memory: %llu GB\n", gBytes);

        unsigned long long newBytes = kBytes * 1024;
        unsigned long long repageSize = pageSize * 1024;
        unsigned long long ptEntries = newBytes / repageSize;

        printf("total number of pages: %llu \n", ptEntries);
        printf("total number of PTE(page table entries): %llu \n", ptEntries);
        unsigned long long ptableSize = ptEntries * 4;
        printf("size of page table: %llu B\n", ptableSize);
        int vpN = log2(ptEntries);
        printf("number of bits for VPN: %llu \n", vpN);
        int offset = bitNumber - vpN;
        printf("number of bits for page offset: %llu \n", offset);
        unsigned long long ptePage = ptableSize / 1024;
        printf("number of PTE in a page of page table: %llu \n", ptePage);
        unsigned long long pNum = ptePage / pageSize;
        printf("number of pages in a page table: %llu \n", pNum);
        unsigned long long pdIndex = log2(pNum);
        printf("number of bits for page directory index: %llu \n", pdIndex);
        unsigned long long ptIndex = vpN - pdIndex;
        printf("number of bits for page table index: %llu \n", ptIndex);

        int a[bitNumber], b[vpN], c[offset];
        int n, i, j, k;
        // Enter decimal Number
        printf("Enter a decimal virtual address:\n");
        scanf("%d", &n);

        if (n > pow(2, bitNumber))
        {
            printf("Virtual address is too large for the memory size.\n");
            exit(0);
        }

        unsigned dvpN = n / (pageSize * 1024);

        printf("VPN of the address: %u \n", dvpN);

        int pOffset = n % (pageSize * 1024);

        printf("page offset of the address: %d\n", pOffset);

        // int pdiDec = log2(vpN) * 1024;

        // printf("page directory index in decimal: %d\n", pdiDec);

        // int ptiDec = ptIndex * 1024;

        // printf("page table index in decimal: %d\n", ptiDec);

        // for (i = 0; n > 0; i++)
        // {
        //     a[i] = n % 2;
        //     n = n / 2;
        // }

        for (i = 0; n > 0; i++)
        {
            a[i] = n % 2;
            n = n / 2;
        }

        while (i < bitNumber)
        {
            a[i] = 0;
            i++;
        }
        printf("input address in binary: ");

        for (i = i - 1; i >= 0; i--)
        {
            printf("%d", a[i]);
        }
        // VPN address in binary
        for (j = 0; dvpN > 0; j++)
        {
            b[j] = dvpN % 2;
            dvpN = dvpN / 2;
        }

        while (j < vpN)
        {
            b[j] = 0;
            j++;
        }
        printf("\nVPN of the address in binary: ");

        for (j = j - 1; j >= 0; j--)
        {
            printf("%d", b[j]);
        }

        // offset address in binary

        for (k = 0; pOffset > 0; k++)
        {
            c[k] = pOffset % 2;
            pOffset = pOffset / 2;
        }

        while (k < offset)
        {
            c[k] = 0;
            k++;
        }
        printf("\npage offset of the address in binary: ");

        for (k = k - 1; k >= 0; k--)
        {
            printf("%d", c[k]);
        }

        printf("\npage directory index in binary: ");

        int pdiBin[pdIndex];
        int l;
        for (l = vpN - 1; l >= vpN - pdIndex; l--)
        {
            pdiBin[l] = b[l];
            printf("%d", pdiBin[l]);
        }

        // for (int i = 0; i < pdIndex; i++)
        // {
        //     printf("\n%d", pdiBin[i]);
        // }

        printf("\npage table index in binary: ");

        int ptiBin[ptIndex];
        int m;
        for (m = (vpN - 1) - pdIndex; m >= 0; m--)
        {
            ptiBin[m] = b[m];
            printf("%d", ptiBin[m]);
        }

        // int pdiResult = 0;
        // for (int x = 0; x <= pdIndex; x++)
        // {
        //     pdiResult = 10 * pdiResult + pdiBin[x];
        // }
        // printf("\n%d", pdiResult);
        // page directory index in decimal format
        int z = sizeof(pdiBin) / sizeof(pdiBin[0]);
        int pdiDec = 0;
        int remM;
        int q;

        for (q = z - 1; q >= 0; q--)
        {
            remM = pdiBin[q] % 10;
            // printf("\n%d", remM);
            pdiDec += (remM) * (pow(2, q));
        }
        printf("\npage directory index in decimal: %d", pdiDec);

        int y = sizeof(ptiBin) / sizeof(ptiBin[0]);
        int ptiDec = 0;
        int rem;

        for (int i = y - 1; i >= 0; i--)
        {
            rem = ptiBin[i] % 10;
            // printf("\n%d", rem);
            ptiDec += (rem) * (pow(2, i));
        }
        printf("\npage table index in decimal: %d", ptiDec);
        // int o = pdIndex;
        // for (i = 0; i < o; ++i)
        // {
        //     pdiDec = 10 * pdiDec + pdiBin[i];
        // }
        // int dvpnArr[vpN];
        // int o = vpN;
        // int p = 0;
        // for (int i = 0; i < o; i++)
        // {
        //     p = p * 10 + vpnArr[i];
        // }
        // printf("%d", p);

        // int rev;
        // int temp;
        // for (rev = 0; rev < bitNumber / 2; rev++)
        // {
        //     temp = a[rev];
        //     a[rev] = a[bitNumber - rev - 1];
        //     a[bitNumber - rev - 1] = temp;
        // }
        // printf("\nVPN of the address in binary: ");
        // int vpnArr[vpN];
        // for (int k = bitNumber - 1; k >= bitNumber - vpN; k--)
        // {
        //     vpnArr[k] = a[k];
        //     printf("%d", vpnArr[k]);
        // }

        // printf("\npage offset of the address in binary: ");
        // int offArr[offset];
        // for (int k = (bitNumber - vpN) - 1; k >= 0; k--)
        // {
        //     offArr[k] = a[k];
        //     printf("%d", offArr[k]);
        // }

        // int v = sizeof(vpnArr) / sizeof(vpnArr[0]);
        // int vpnDec = 0;

        // for (int q = v - 1; q >= 0; q--)
        // {
        //     int rem = vpnArr[q] % 10;
        //     printf("\n%d", rem);
        //     vpnDec += (rem) * (pow(2, q));
        // }
        // printf("\nVPN of the address: %d", vpnDec);
    }
    else
    {
        printf("Must print first argument as 1 or 2.");
        exit(0);
    }
}