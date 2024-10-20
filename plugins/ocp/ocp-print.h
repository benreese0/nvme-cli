/* SPDX-License-Identifier: GPL-2.0-or-later */
#ifndef OCP_PRINT_H
#define OCP_PRINT_H

#include "ocp-hardware-component-log.h"
#include "ocp-fw-activation-history.h"
#include "ocp-telemetry-decode.h"
#include "ocp-nvme.h"

struct ocp_print_ops {
	void (*hwcomp_log)(struct hwcomp_log *log, __u32 id, bool list);
	void (*fw_act_history)(const struct fw_activation_history *fw_history);
	void (*smart_extended_log)(void *data);
	void (*telemetry_log)(struct ocp_telemetry_parse_options *options);
	void (*c3_log)(struct nvme_dev *dev, struct ssd_latency_monitor_log *log_data);
	void (*c5_log)(struct nvme_dev *dev, struct unsupported_requirement_log *log_data);
	nvme_print_flags_t flags;
};

struct ocp_print_ops *ocp_get_stdout_print_ops(nvme_print_flags_t flags);
struct ocp_print_ops *ocp_get_binary_print_ops(nvme_print_flags_t flags);

#ifdef CONFIG_JSONC
struct ocp_print_ops *ocp_get_json_print_ops(nvme_print_flags_t flags);
#else /* !CONFIG_JSONC */
static inline struct ocp_print_ops *ocp_get_json_print_ops(nvme_print_flags_t flags)
{
	return NULL;
}
#endif /* !CONFIG_JSONC */

void ocp_show_hwcomp_log(struct hwcomp_log *log, __u32 id, bool list, nvme_print_flags_t flags);
void ocp_fw_act_history(const struct fw_activation_history *fw_history, nvme_print_flags_t flags);
void ocp_smart_extended_log(void *data, nvme_print_flags_t flags);
void ocp_show_telemetry_log(struct ocp_telemetry_parse_options *options, nvme_print_flags_t flags);
void ocp_c3_log(struct nvme_dev *dev, struct ssd_latency_monitor_log *log_data,
		nvme_print_flags_t flags);
void ocp_c5_log(struct nvme_dev *dev, struct unsupported_requirement_log *log_data,
		nvme_print_flags_t flags);
#endif /* OCP_PRINT_H */