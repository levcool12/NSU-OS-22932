#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ulimit.h>
#include <sys/types.h>
#include <sys/resource.h>


extern char *optarg;
extern int optind, opterr, optopt;

extern char** environ;
struct rlimit rlp;


int main(int argc, char* argv[])
{
	char options[] = "vV:disupU:cC:",  *f_ptr, *g_ptr, *tmp;
	int c, invalid = 0, dflg = 0, fflg = 0, gflg = 0, argc_cpy = argc;
	long unew;
	if (argc == 1)
	{
		printf("Неверное количество аргументов");
		exit(1);
	}
	while (argc_cpy > 1)
	{
		tmp = argv[argc - argc_cpy + 1];
		argv[argc - argc_cpy + 1] = argv[argc_cpy - 1];
		argv[argc_cpy - 1] = tmp;
		argc_cpy--;
	}
	printf("argc равно %d\n", argc);
	while ((c = getopt(argc, argv, options)) != EOF)
	{
		switch (c)
		{
			case 'v':
				printf("Переменные:\n");
				for (char** i = environ; *i != NULL; i++)
					printf("%s\n", *i);
				break;
			case 'V':
				if (putenv(optarg) != 0)
					fprintf(stderr, "Ошибка, невозможно изменить аргумент");
				break;
			case 'd':
				printf("Текущий каталог:\n%s\n", getcwd(NULL, 200));;
				break;
			case 'i':
				 printf("Эффективный идентификатор группы: %d\n", getegid());
				 printf("Реальный идентификатор группы: %d\n", getgid());
				 printf("Эффективный идентификатор пользователя: %d\n", geteuid());
				 printf("Реальный идентификатор пользователя: %d\n", getuid());
				 break;
			case 's':
				if (setpgid(getpid(), getpgid(getpid())) == 0)
					printf("Процесс успешно установлен в качестве лидера группы\n");
				break;
			case 'u':
				printf("%ld - ulimit\n", ulimit(UL_GETFSIZE));
				break;
			case 'p':
				printf("Идентификатор процесса: %ld\nИдентификатор родительского процесса: %ld\nИдентификатор группы: %ld\n", getpid(), getppid(), getpgid(getpid()));
				break;
			case 'U':
				unew = atol(optarg);
				printf("Старый лимит: %ld\n", ulimit(UL_GETFSIZE));
				int a = ulimit(UL_SETFSIZE, unew);
				if (a == -1)
					fprintf(stderr, "Ошибка, слишком большой аргумент для ulimit\n");
				printf("Новый лимит: %ld\n", ulimit(UL_GETFSIZE));
				break;
			case 'c':
				getrlimit(RLIMIT_CORE, &rlp);
				printf("%ld - core\n", rlp.rlim_cur);
				break;
			case 'C':
				getrlimit(RLIMIT_CORE, &rlp);
				rlp.rlim_cur = atol(optarg);
				int lim = setrlimit(RLIMIT_CORE, &rlp);
				if (lim == -1)
					fprintf(stderr, "Ошибка, слишком большой аргумент для core\n");
				break;
			case '?':
			  printf("Неверный параметр: %c\n", optopt);
			  invalid++;
			break;
		}
		
	}
	printf("invalid равно %d\n", invalid);
	printf("optind равно %d\n", optind);
	  if (optind < argc)
		  printf("следующий параметр = %s\n", argv[optind]);
}