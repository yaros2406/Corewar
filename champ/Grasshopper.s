.name		"Grasshopper"
.comment	"skip-skip-skip"

jump:			sti r1, %:back, %4				# обозначаем live
				sti r1, %:jump, %15				#
				live %42
				ld  %1, r2						# подгружаем код live в r2
				sti r2, %124, r5				# live
				sti r1, %122, r5				#
				ld  %-11, r4					# подгружаем значение zjmp
				sti r4, %115, r5				# определяем адрес для zjmp
				ld  %9, r3						# подгружаем код zjmp в r3
				sti r3, %100, r5				# определяем параметры прыжка
				ld %25, r6						# выполняем смещение
				add r5, r6, r5					# просчитываем след. адрес

back:
				fork	%:jump					# назад к jump
				live %42
				sub r5, r6, r7					# прыгаем на последний адрес
				ld  %20, r8						# вычисляем смещение для след. zjmp
				add r7, r8, r7					# вычисляем адрес для след. zjmp
				sti r7, %:back, %53				# записываем его
				ld %9, r9						# подгружаем код для прыжка
				sti r9, %:back, %51				# записываем его
				add r10, r10, r10				# carry -> 1
