// Composables
import { createRouter, createWebHistory } from 'vue-router';

const routes = [
  {
    path: '/',
    component: () => import('@/layouts/default/Default.vue'),
    children: [
      {
        path: '',
        name: 'Home',
        component: () => import('@/views/Home.vue'),
      },
      {
        path: '/bubble-sort',
        name: 'BubbleSort',
        component: () => import('@/views/sorts/BubbleSort.vue'),
      },
      {
        path: '/selection-sort',
        name: 'SelectionSort',
        component: () => import('@/views/sorts/SelectionSort.vue'),
      },
      {
        path: '/insertion-sort',
        name: 'InsertionSort',
        component: () => import('@/views/sorts/InsertionSort.vue'),
      },
      {
        path: '/merge-sort',
        name: 'MergeSort',
        component: () => import('@/views/sorts/MergeSort.vue'),
      },
      {
        path: '/iterative-merge-sort',
        name: 'IterativeMergeSort',
        component: () => import('@/views/sorts/IterativeMergeSort.vue'),
      },
      {
        path: '/iterative-quick-sort',
        name: 'IterativeQuickSort',
        component: () => import('@/views/sorts/IterativeQuickSort.vue'),
      }
    ],
  },
];

const router = createRouter({
  history: createWebHistory(import.meta.env.BASE_URL),
  routes,
});

export default router;
