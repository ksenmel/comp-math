# Сингулярное разложение и сжатие изображений
[Репозиторий](https://github.com/ksenmel/svd-compress/tree/main) с реализацией утилиты.

## Аппаратное обеспечение
- Процессор — **Apple M2**
- Оперативная память — **8 GB**
- Операционная система — **macOS Ventura 13.0**

## Реализованные алгоритмы SVD
- numpy
- power-iterations
- block-power-iterations

## Эксперимент

Были взяты следующие значения для степени сжатия: 2, 5, 10, 20, 50, 100. Однако не все изображения удалось сжать в 50 и 100 раз, из-за недостаточного размера самих изображений.