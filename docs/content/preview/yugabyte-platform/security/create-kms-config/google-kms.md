---
title: Create a KMS configuration using Google Cloud
headerTitle: Create a KMS configuration using Google Cloud
linkTitle: Create a KMS configuration
description: Use YugabyteDB Anywhere to create a KMS configuration for Google Cloud KMS.
aliases:
  - /preview/yugabyte-platform/security/create-kms-config
menu:
  preview_yugabyte-platform:
    parent: security
    identifier: create-kms-config-1-google-kms
    weight: 27
type: docs
---

<ul class="nav nav-tabs-alt nav-tabs-yb">
  <li >
    <a href="{{< relref "./aws-kms.md" >}}" class="nav-link">
      <i class="fa-brands fa-aws" aria-hidden="true"></i>
      AWS KMS
    </a>
  </li>
  <li >
    <a href="{{< relref "./google-kms.md" >}}" class="nav-link active">
      <i class="fa-brands fa-google" aria-hidden="true"></i>
      Google KMS
    </a>
  </li>

  <li >
    <a href="{{< relref "./azure-kms.md" >}}" class="nav-link">
      <i class="icon-azure" aria-hidden="true"></i>
      &nbsp;&nbsp;&nbsp;&nbsp;Azure KMS
    </a>
  </li>

  <li >
    <a href="{{< relref "./hashicorp-kms.md" >}}" class="nav-link">
      <i class="icon-postgres" aria-hidden="true"></i>
      HashiCorp Vault
    </a>
  </li>

</ul>

<br>Encryption at rest uses universe keys to encrypt and decrypt universe data keys. You can use the YugabyteDB Anywhere UI to create key management service (KMS) configurations for generating the required universe keys for one or more YugabyteDB universes. Encryption at rest in YugabyteDB Anywhere supports the use of [Google Cloud KMS](https://cloud.google.com/security-key-management).

Conceptually, Google Cloud KMS consists of a key ring containing one or more cryptographic keys, with each key capable of having multiple versions.

The Google Cloud user associated with a KMS configuration requires a custom role assigned to the service account with the following KMS-related permissions:

- `cloudkms.keyRings.create`
- `cloudkms.keyRings.get`
- `cloudkms.cryptoKeys.create`
- `cloudkms.cryptoKeys.get`
- `cloudkms.cryptoKeyVersions.useToEncrypt`
- `cloudkms.cryptoKeyVersions.useToDecrypt`
- `cloudkms.locations.generateRandomBytes`

If you are planning to use an existing cryptographic key with the same name, it must meet the following criteria:

- The primary cryptographic key version should be in the Enabled state.
- The purpose should be set to symmetric ENCRYPT_DECRYPT.
- The key rotation period should be set to Never (manual rotation).

You can create a KMS configuration that uses Google Cloud KMS, as follows:

1. Use the YugabyteDB Anywhere UI to navigate to **Configs > Security > Encryption At Rest** to access the list of existing configurations.

1. Click **Create New Config**.

3. Enter the following configuration details in the form:

    - **Configuration Name** — Enter a meaningful name for your configuration.
    - **KMS Provider** — Select **GCP KMS**.
    - **Service Account Credentials** — Upload the JSON file containing your Google Cloud credentials.
    - **Location** — Select the region where your crypto key is located.
    - **Key Ring Name** — Enter the name of the key ring. If a key ring with the same name already exists, the existing key ring is used; otherwise, a new key ring is created automatically.
    - **Crypto Key Name** — Enter the name of the crypto key. If a crypto key with the same name already exists in the key ring, the settings are validated and the existing crypto key is used; otherwise, a new crypto key is created automatically.
    - **Protection Level** — Select the crypto key protection at either the software or hardware level.
    - **KMS Endpoint** — Optionally, specify a custom Google Cloud KMS endpoint to route the encryption traffic.

    ![Google KMS](/images/yp/security/googlekms-config.png)

3. Click **Save**.<br>

    Your new configuration should appear in the list of configurations. A saved KMS configuration can only be deleted if it is not in use by any existing universes.

4. Optionally, to confirm that the information is correct, click **Show details**. Note that sensitive configuration values are displayed partially masked.



Note that YugabyteDB Anywhere does not manage the key ring and deleting the KMS configuration does not destroy the key ring, cryptographic key, or its versions on Google Cloud KMS.
