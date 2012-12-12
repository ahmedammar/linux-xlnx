#include <asm/io.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/of_platform.h>
#include <linux/of.h>
#include <linux/platform_device.h>
#include <linux/of_address.h>
#include <linux/slab.h>
#include <linux/errno.h>

#define XAPM_GCC_HIGH_OFFSET	0x0000	/**< Global Clock Counter 32 to 63 bits  */
#define XAPM_GCC_LOW_OFFSET	0x0004	/**< Global Clock Counter Lower 0-31 bits  */
#define XAPM_SI_HIGH_OFFSET	0x0020	/**< Sample Interval MSB */
#define XAPM_SI_LOW_OFFSET	0x0024	/**< Sample Interval LSB */
#define XAPM_SICR_OFFSET	0x0028	/**< Sample Interval Control Register */

#define XAPM_GIE_OFFSET		0x0030	/**< Global Interrupt Enable Register */
#define XAPM_IE_OFFSET		0x0034	/**< Interrupt Enable Register */
#define XAPM_IS_OFFSET		0x0038	/**< Interrupt Status Register */

#define XAPM_AGENT_OFFSET	0x0040	/**< Agent Selector Register */

#define XAPM_MSR0_OFFSET	0x0044	/**< Metric Selector 0 Register */
#define XAPM_MSR1_OFFSET	0x0048	/**< Metric Selector 1 Register */
#define XAPM_MSR2_OFFSET	0x004C	/**< Metric Selector 2 Register */

#define XAPM_MC0_OFFSET		0x0100	/**< Metric Counter 0 Register */
#define XAPM_INC0_OFFSET	0x0104	/**< Incrementer 0 Register */
#define XAPM_RANGE0_OFFSET	0x0108	/**< Range 0 Register */
#define XAPM_MC1_OFFSET		0x0110	/**< Metric Counter 1 Register */
#define XAPM_INC1_OFFSET	0x0114	/**< Incrementer 1 Register */
#define XAPM_RANGE1_OFFSET	0x0118	/**< Range 1 Register */
#define XAPM_MC2_OFFSET		0x0120	/**< Metric Counter 2 Register */
#define XAPM_INC2_OFFSET	0x0124	/**< Incrementer 2 Register */
#define XAPM_RANGE2_OFFSET	0x0128	/**< Range 2 Register */
#define XAPM_MC3_OFFSET		0x0130	/**< Metric Counter 3 Register */
#define XAPM_INC3_OFFSET	0x0134	/**< Incrementer 3 Register */
#define XAPM_RANGE3_OFFSET	0x0138	/**< Range 3 Register */
#define XAPM_MC4_OFFSET		0x0140	/**< Metric Counter 4 Register */
#define XAPM_INC4_OFFSET	0x0144	/**< Incrementer 4 Register */
#define XAPM_RANGE4_OFFSET	0x0148	/**< Range 4 Register */
#define XAPM_MC5_OFFSET		0x0150	/**< Metric Counter 5 Register */
#define XAPM_INC5_OFFSET	0x0154	/**< Incrementer 5 Register */
#define XAPM_RANGE5_OFFSET	0x0158	/**< Range 5 Register */
#define XAPM_MC6_OFFSET		0x0160	/**< Metric Counter 6 Register */
#define XAPM_INC6_OFFSET	0x0164	/**< Incrementer 6 Register */
#define XAPM_RANGE6_OFFSET	0x0168	/**< Range 6 Register */
#define XAPM_MC7_OFFSET		0x0170	/**< Metric Counter 7 Register */
#define XAPM_INC7_OFFSET	0x0174	/**< Incrementer 7 Register */
#define XAPM_RANGE7_OFFSET	0x0178	/**< Range 7 Register */
#define XAPM_MC8_OFFSET		0x0180	/**< Metric Counter 8 Register */
#define XAPM_INC8_OFFSET	0x0184	/**< Incrementer 8 Register */
#define XAPM_RANGE8_OFFSET	0x0188	/**< Range 8 Register */
#define XAPM_MC9_OFFSET		0x0190	/**< Metric Counter 9 Register */
#define XAPM_INC9_OFFSET	0x0194	/**< Incrementer 9 Register */
#define XAPM_RANGE9_OFFSET	0x0198	/**< Range 9 Register */

#define XAPM_SMC0_OFFSET	0x0200	/**< Sampled Metric Counter 0 Register */
#define XAPM_SINC0_OFFSET	0x0204	/**< Sampled Incrementer 0 Register */
#define XAPM_SMC1_OFFSET	0x0210	/**< Sampled Metric Counter 1 Register */
#define XAPM_SINC1_OFFSET	0x0214	/**< Sampled Incrementer 1 Register */
#define XAPM_SMC2_OFFSET	0x0220	/**< Sampled Metric Counter 2 Register */
#define XAPM_SINC2_OFFSET	0x0224	/**< Sampled Incrementer 2 Register */
#define XAPM_SMC3_OFFSET	0x0230	/**< Sampled Metric Counter 3 Register */
#define XAPM_SINC3_OFFSET	0x0234	/**< Sampled Incrementer 3 Register */
#define XAPM_SMC4_OFFSET	0x0240	/**< Sampled Metric Counter 4 Register */
#define XAPM_SINC4_OFFSET	0x0244	/**< Sampled Incrementer 4 Register */
#define XAPM_SMC5_OFFSET	0x0250	/**< Sampled Metric Counter 5 Register */
#define XAPM_SINC5_OFFSET	0x0254	/**< Sampled Incrementer 5 Register */
#define XAPM_SMC6_OFFSET	0x0260	/**< Sampled Metric Counter 6 Register */
#define XAPM_SINC6_OFFSET	0x0264	/**< Sampled Incrementer 6 Register */
#define XAPM_SMC7_OFFSET	0x0270	/**< Sampled Metric Counter 7 Register */
#define XAPM_SINC7_OFFSET	0x0274	/**< Sampled Incrementer 7 Register */
#define XAPM_SMC8_OFFSET	0x0280	/**< Sampled Metric Counter 8 Register */
#define XAPM_SINC8_OFFSET	0x0284	/**< Sampled Incrementer 8 Register */
#define XAPM_SMC9_OFFSET	0x0290	/**< Sampled Metric Counter 9 Register */
#define XAPM_SINC9_OFFSET	0x0294	/**< Sampled Incrementer 9 Register */



#define XAPM_CTL_OFFSET	 	0x0300	/**< Control Register */
#define XAPM_FEC_OFFSET	 	0x0400	/**< Flag Enable Control Register */
#define XAPM_SWD_OFFSET	 	0x0404	/**< Software-written Data Register */

#define XAPM_SICR_MCNTR_RST_MASK	0x00000100 /**< Enable the Metric Counter Reset */
#define XAPM_SICR_LOAD_MASK		0x00000002 /**< Load the Sample Interval Register Value into the counter */
#define XAPM_SICR_ENABLE_MASK		0x00000001 /**< Enable the downcounter */

#define XAPM_IXR_MC9_OVERFLOW_MASK   	0x00001000 /**< Metric Counter 9 Overflow> */
#define XAPM_IXR_MC8_OVERFLOW_MASK   	0x00000800 /**< Metric Counter 8 Overflow> */
#define XAPM_IXR_MC7_OVERFLOW_MASK   	0x00000400 /**< Metric Counter 7 Overflow> */
#define XAPM_IXR_MC6_OVERFLOW_MASK   	0x00000200 /**< Metric Counter 6 Overflow> */
#define XAPM_IXR_MC5_OVERFLOW_MASK   	0x00000100 /**< Metric Counter 5 Overflow> */
#define XAPM_IXR_MC4_OVERFLOW_MASK   	0x00000080 /**< Metric Counter 4 Overflow> */
#define XAPM_IXR_MC3_OVERFLOW_MASK   	0x00000040 /**< Metric Counter 3 Overflow> */
#define XAPM_IXR_MC2_OVERFLOW_MASK   	0x00000020 /**< Metric Counter 2 Overflow> */
#define XAPM_IXR_MC1_OVERFLOW_MASK   	0x00000010 /**< Metric Counter 1 Overflow> */
#define XAPM_IXR_MC0_OVERFLOW_MASK   	0x00000008 /**< Metric Counter 0 Overflow> */
#define XAPM_IXR_FIFO_FULL_MASK   	0x00000004 /**< Event Log FIFO full> */
#define XAPM_IXR_SIC_OVERFLOW_MASK   	0x00000002 /**< Sample Interval Counter Overflow> */
#define XAPM_IXR_GCC_OVERFLOW_MASK	0x00000001 /**< Global Clock Counter Overflow> */
#define XAPM_IXR_ALL_MASK		(XAPM_IXR_SIC_OVERFLOW_MASK | \
					XAPM_IXR_GCC_OVERFLOW_MASK |  \
					XAPM_IXR_FIFO_FULL_MASK | \
					XAPM_IXR_MC0_OVERFLOW_MASK | \
					XAPM_IXR_MC1_OVERFLOW_MASK | \
					XAPM_IXR_MC2_OVERFLOW_MASK | \
					XAPM_IXR_MC3_OVERFLOW_MASK | \
					XAPM_IXR_MC4_OVERFLOW_MASK | \
					XAPM_IXR_MC5_OVERFLOW_MASK | \
					XAPM_IXR_MC6_OVERFLOW_MASK | \
					XAPM_IXR_MC7_OVERFLOW_MASK | \
					XAPM_IXR_MC8_OVERFLOW_MASK | \
					XAPM_IXR_MC9_OVERFLOW_MASK)

#define XAPM_CR_FIFO_RESET_MASK    	0x02000000
					/**< FIFO Reset */
#define XAPM_CR_MUXSEL_MASK	    	0x01000000
					/**< Mux Selector Mask */
#define XAPM_CR_GCC_RESET_MASK	   	0x00020000
					/**< Global Clk Counter Reset */
#define XAPM_CR_GCC_ENABLE_MASK	   	0x00010000
					/**< Global Clk Counter Enable */
#define XAPM_CR_EVENTLOG_ENABLE_MASK  	0x00000100
					/**< Event Log Enable */
#define XAPM_CR_MCNTR_RESET_MASK   	0x00000002
					/**< Metrics Counter Reset */
#define XAPM_CR_MCNTR_ENABLE_MASK  	0x00000001
					/**< Metrics Counter Enable */

#define XAPM_MAX_COUNTERS		10 /**< Maximum number of Counters */

#define XAPM_METRIC_COUNTER_0	0 /**< Metric Counter 0 Register Index */
#define XAPM_METRIC_COUNTER_1	1 /**< Metric Counter 1 Register Index */
#define XAPM_METRIC_COUNTER_2	2 /**< Metric Counter 2 Register Index */
#define XAPM_METRIC_COUNTER_3	3 /**< Metric Counter 3 Register Index */
#define XAPM_METRIC_COUNTER_4	4 /**< Metric Counter 4 Register Index */
#define XAPM_METRIC_COUNTER_5	5 /**< Metric Counter 5 Register Index */
#define XAPM_METRIC_COUNTER_6	6 /**< Metric Counter 6 Register Index */
#define XAPM_METRIC_COUNTER_7	7 /**< Metric Counter 7 Register Index */
#define XAPM_METRIC_COUNTER_8	8 /**< Metric Counter 8 Register Index */
#define XAPM_METRIC_COUNTER_9	9 /**< Metric Counter 9 Register Index */

#define XAPM_INCREMENTER_0	0 /**< Metric Counter 0 Register Index */
#define XAPM_INCREMENTER_1	1 /**< Metric Counter 0 Register Index */
#define XAPM_INCREMENTER_2	2 /**< Metric Counter 0 Register Index */
#define XAPM_INCREMENTER_3	3 /**< Metric Counter 0 Register Index */
#define XAPM_INCREMENTER_4	4 /**< Metric Counter 0 Register Index */
#define XAPM_INCREMENTER_5	5 /**< Metric Counter 0 Register Index */
#define XAPM_INCREMENTER_6	6 /**< Metric Counter 0 Register Index */
#define XAPM_INCREMENTER_7	7 /**< Metric Counter 0 Register Index */
#define XAPM_INCREMENTER_8	8 /**< Metric Counter 0 Register Index */
#define XAPM_INCREMENTER_9	9 /**< Metric Counter 0 Register Index */

#define XAPM_METRIC_SET_0	0 /**< Metrics Set 0 */
#define XAPM_METRIC_SET_1	1 /**< Metrics Set 1 */
#define XAPM_METRIC_SET_2	2 /**< Metrics Set 2 */
#define XAPM_METRIC_SET_3	3 /**< Metrics Set 3 */
#define XAPM_METRIC_SET_4	4 /**< Metrics Set 4 */
#define XAPM_METRIC_SET_5	5 /**< Metrics Set 5 */
#define XAPM_METRIC_SET_6	6 /**< Metrics Set 6 */
#define XAPM_METRIC_SET_7	7 /**< Metrics Set 7 */
#define XAPM_METRIC_SET_8	8 /**< Metrics Set 7 */
#define XAPM_METRIC_SET_9	9 /**< Metrics Set 7 */
#define XAPM_METRIC_SET_10	10 /**< Metrics Set 7 */
#define XAPM_METRIC_SET_11	11 /**< Metrics Set 7 */
#define XAPM_METRIC_SET_16	16 /**< Metrics Set 7 */
#define XAPM_METRIC_SET_17	17 /**< Metrics Set 7 */
#define XAPM_METRIC_SET_18	18 /**< Metrics Set 7 */
#define XAPM_METRIC_SET_19	19 /**< Metrics Set 7 */
#define XAPM_METRIC_SET_20	20 /**< Metrics Set 7 */
#define XAPM_METRIC_SET_21	21 /**< Metrics Set 7 */
#define XAPM_METRIC_SET_22	22 /**< Metrics Set 7 */
#define XAPM_METRIC_SET_32	32 /**< Metrics Set 7 */
#define XAPM_METRIC_SET_33	33 /**< Metrics Set 7 */

#define XAPM_MAX_AGENTS 	9 /**< Maximum number of Agents */

#define XAPM_FLAG_WRADDR	0x000001 /**< Write Address Flag */
#define XAPM_FLAG_FIRSTWR	0x000002 /**< First Write Flag */
#define XAPM_FLAG_LASTWR	0x000004 /**< Last Write Flag */
#define XAPM_FLAG_RESPONSE	0x000008 /**< Response Flag */
#define XAPM_FLAG_RDADDR	0x000010 /**< Read Address Flag */
#define XAPM_FLAG_FIRSTRD	0x000020 /**< First Read Flag */
#define XAPM_FLAG_LASTRD	0x000040 /**< Last Read Flag */
#define XAPM_FLAG_SWDATA	0x010000 /**< Software-written Data Flag */

struct xilinx_perfmon_dev {
    void __iomem *regs;
    struct device *dev;
};

struct xilinx_perfmon_dev *gdev;

int xilinx_perfmon_intr_wait(struct xilinx_perfmon_dev *dev)
{
	while (!(readl_relaxed(dev->regs + XAPM_IS_OFFSET) & XAPM_IXR_SIC_OVERFLOW_MASK))
		cpu_relax();

	return 0;
}

int xilinx_perfmon_intr_clear(struct xilinx_perfmon_dev *dev)
{
	u32 reg = readl_relaxed(dev->regs + XAPM_IS_OFFSET);
	reg |= XAPM_IXR_SIC_OVERFLOW_MASK;
	writel_relaxed(reg, dev->regs + XAPM_IS_OFFSET);
	return 0;
}

int xilinx_perfmon_agent_set(struct xilinx_perfmon_dev *dev, u8 agent)
{
	writel_relaxed(agent, dev->regs + XAPM_AGENT_OFFSET);
	return 0;
}

int xilinx_perfmon_interval_enable(struct xilinx_perfmon_dev *dev)
{
	writel_relaxed(XAPM_SICR_ENABLE_MASK, dev->regs + XAPM_SICR_OFFSET);
	return 0;
}

int xilinx_perfmon_interval_load(struct xilinx_perfmon_dev *dev)
{
	writel_relaxed(XAPM_SICR_LOAD_MASK, dev->regs + XAPM_SICR_OFFSET);
	return 0;
}

int xilinx_perfmon_interval_set(struct xilinx_perfmon_dev *dev, u32 high, u32 low)
{
	// TODO (high/low)
	writel_relaxed(low, dev->regs + XAPM_SI_LOW_OFFSET);
	return 0;
}

int xilinx_perfmon_mcounter_set(struct xilinx_perfmon_dev *dev, u8 metrics, u8 counter)
{
	u32 reg = readl_relaxed(dev->regs + XAPM_MSR0_OFFSET);
	reg |= (metrics << (counter * 8));
	writel_relaxed(reg, dev->regs + XAPM_MSR0_OFFSET);
	return 0;
}

int xilinx_perfmon_mcounter_reset(struct xilinx_perfmon_dev *dev)
{
	u32 reg = readl_relaxed(dev->regs + XAPM_CTL_OFFSET);
	reg |= XAPM_CR_MCNTR_RESET_MASK;
	writel_relaxed(reg, dev->regs + XAPM_CTL_OFFSET);

	reg &= ~XAPM_CR_MCNTR_RESET_MASK;
	writel_relaxed(reg, dev->regs + XAPM_CTL_OFFSET);
	return 0;
}

int xilinx_perfmon_mcounter_enable(struct xilinx_perfmon_dev *dev)
{
	u32 reg = readl_relaxed(dev->regs + XAPM_CTL_OFFSET);
	reg |= XAPM_CR_MCNTR_ENABLE_MASK;
	writel_relaxed(reg, dev->regs + XAPM_CTL_OFFSET);
	return 0;
}

int xilinx_perfmon_mcounter_disable(struct xilinx_perfmon_dev *dev)
{
	u32 reg = readl_relaxed(dev->regs + XAPM_CTL_OFFSET);
	reg &= ~XAPM_CR_MCNTR_ENABLE_MASK;
	writel_relaxed(reg, dev->regs + XAPM_CTL_OFFSET);

	return 0;
}

u32 xilinx_perfmon_mcounter_get(struct xilinx_perfmon_dev *dev, u8 counter)
{
	u32 reg = readl_relaxed(dev->regs +  XAPM_MC0_OFFSET + (counter * 16));
	return reg;
}

int xilinx_perfmon_init(struct xilinx_perfmon_dev *dev)
{
	xilinx_perfmon_mcounter_set(dev, XAPM_METRIC_SET_2, XAPM_METRIC_COUNTER_0);
	xilinx_perfmon_mcounter_set(dev, XAPM_METRIC_SET_3, XAPM_METRIC_COUNTER_1);
	xilinx_perfmon_mcounter_enable(dev);
	xilinx_perfmon_interval_set(dev, 0, 166666666);

	return 0;
}

int xilinx_perfmon_run_begin(void)
{
	xilinx_perfmon_mcounter_reset(gdev);
	xilinx_perfmon_agent_set(gdev, 0);
	xilinx_perfmon_interval_load(gdev);
	xilinx_perfmon_mcounter_enable(gdev);
	xilinx_perfmon_interval_enable(gdev);
	return 0;
}
EXPORT_SYMBOL_GPL(xilinx_perfmon_run_begin);

int xilinx_perfmon_run_end(void)
{
	u32 c[2];
	xilinx_perfmon_intr_wait(gdev);
	xilinx_perfmon_intr_clear(gdev);
	c[0] = xilinx_perfmon_mcounter_get(gdev, 0);
	c[1] = xilinx_perfmon_mcounter_get(gdev, 1);

	pr_info("xilinx_perfmon: tx:%uMB/s rx:%uMB/s]\n", c[0]/1048576, c[1]/1048576);
	pr_info("xilinx_perfmon: tx:%ufps rx:%ufps]\n", c[0]/(1920*1080*4), c[1]/(1920*1080*4));
	return 0;
}
EXPORT_SYMBOL_GPL(xilinx_perfmon_run_end);

static int __devinit xilinx_perfmon_probe(struct platform_device *op)
{
	struct xilinx_perfmon_dev *xdev;
	struct device_node *node;
	int err;

	xdev = kzalloc(sizeof(struct xilinx_perfmon_dev), GFP_KERNEL);
	if (!xdev) {
		dev_err(&op->dev, "Not enough memory for device\n");
		err = -ENOMEM;
		goto out_return;
	}

	xdev->dev = &(op->dev);
	node = op->dev.of_node;

	xdev->regs = of_iomap(node, 0);
	if (!xdev->regs) {
		dev_err(&op->dev, "unable to iomap registers\n");
		err = -ENOMEM;
		goto out_free_xdev;
	}

	gdev = xdev;
	dev_set_drvdata(&op->dev, xdev);

	xilinx_perfmon_init(xdev);

	return 0;

out_free_xdev:
	kfree(xdev);

out_return:
	return err;
}

static int __devexit xilinx_perfmon_of_remove(struct platform_device *op)
{
	struct xilinx_perfmon_dev *xdev;

	xdev = dev_get_drvdata(&op->dev);
	iounmap(xdev->regs);
	dev_set_drvdata(&op->dev, NULL);
	kfree(xdev);

	return 0;
}

static const struct of_device_id xilinx_perfmon_of_ids[] = {
	{ .compatible = "xlnx,axi-perfmon",},
	{}
};

static struct platform_driver xilinx_perfmon_of_driver = {
	.driver = {
		.name = "xilinx-axi-perfmon",
		.owner = THIS_MODULE,
		.of_match_table = xilinx_perfmon_of_ids,
	},
	.probe = xilinx_perfmon_probe,
	.remove = __devexit_p(xilinx_perfmon_of_remove),
};

static int __init xilinx_perfmon_load(void)
{
	int status;
	status = platform_driver_register(&xilinx_perfmon_of_driver);
	return status;
}
late_initcall(xilinx_perfmon_load);

static void __exit xilinx_perfmon_exit(void)
{
	platform_driver_unregister(&xilinx_perfmon_of_driver);
}
module_exit(xilinx_perfmon_exit);

MODULE_AUTHOR("Ahmed Ammar <aammar@genesi-usa.com>");
MODULE_LICENSE("GPL v2");
