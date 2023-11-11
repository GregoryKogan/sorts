// Utilities
import { defineStore } from 'pinia';

export const useAppStore = defineStore('app', {
  state: () => ({
    frameRate: 0 as number,
    sortAlgorithm: "" as string,
    comparisons: 0 as number,
    swaps: 0 as number,
    sequenceLength: 0 as number,
    stepsPerSecond: 0 as number,
  }),
  actions: {
    setFrameRate(frameRate: number) {
      this.frameRate = frameRate;
    },
    setSortAlgorithm(sortAlgorithm: string) {
      this.sortAlgorithm = sortAlgorithm;
    },
    setComparisons(comparisons: number) {
      this.comparisons = comparisons;
    },
    setSwaps(swaps: number) {
      this.swaps = swaps;
    },
    setSequenceLength(sequenceLength: number) {
      this.sequenceLength = sequenceLength;
    },
    setStepsPerSecond(stepsPerSecond: number) {
      this.stepsPerSecond = stepsPerSecond;
    },
  },
});